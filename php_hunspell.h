#include <stdlib.h>
#include <phpcpp.h>
#include <hunspell/hunspell.hxx>

namespace PhpHunspellExtension {

static const auto NAME = "hunspell";
static const auto VERSION = "0.1";

class Hunspell : public Php::Base {

public:
    Hunspell() {}

    virtual ~Hunspell() {
        delete hunspell;
        hunspell = NULL;
    }

    void __construct(Php::Parameters &params) {
        const char *dic_path = params[0];
        const char *aff_path = params[1];

        if (!strlen(dic_path)) {
            throw Php::Exception("dic_path required");
        }
        if (!strlen(aff_path)) {
            throw Php::Exception("aff_path required");
        }

        _initHunspell(dic_path, aff_path);
    }

    Php::Value addDictionary(Php::Parameters &params) {
        const char *dic_path = params[0];

        if (!strlen(dic_path)) {
            throw Php::Exception("dic_path required");
        }
        
        return _addDictionary(dic_path);
    }

    Php::Value spell(Php::Parameters &params) {
        int result;
        const char *word = params[0];
        if (params.size() > 1) {
            Php::Value extras;
            result = _checkSpelling(word, extras);
            params[1] = extras;
        } else {
            result = _checkSpelling(word);
        }
        return result;
    }

    Php::Value suggest(Php::Parameters &params) {
        const char *word = params[0];
        Php::Array result;
        _suggest(word, result);
        return result;
    }

    Php::Value analyze(Php::Parameters &params) {
        const char *word = params[0];
        Php::Array result;
        _analyze(word, result);
        return result;
    }

    Php::Value stem(Php::Parameters &params) {
        const char *word = params[0];
        Php::Array result;
        if (params.size() > 1 && params[1]) {
            _stem(word, result, params[1]);
        } else {
            _stem(word, result);
        }
        return result;
    }

    Php::Value generate(Php::Parameters &params) {
        const char *word1 = params[0];
        const char *word2 = params[1];
        Php::Array result;
        _generate(word1, word2, result);
        return result;
    }

    Php::Value generateEx(Php::Parameters &params) {
        Php::Array desc = params[1];
        Php::Array result;
        _generate(params[0], desc, result);
        return result;
    }

    Php::Value getDictionaryEncoding() {
        return _h()->get_dic_encoding();
    }

    Php::Value getWordChars() {
        return _h()->get_wordchars();
    }

private:
    ::Hunspell *hunspell = NULL;

    int _phpArrayToCharPp(Php::Array array, char ***stems) {
        int size = array.size();
        int index = 0;
        if (size) {
            *stems = (char **)malloc(sizeof(char *) * size);
            if (NULL == *stems) {
                throw Php::Exception("Memory allocation failed in PhpHunspell::_phpArrayToCharPp");
            }
            for (auto &item : array) {
                const char *s = item.second;
                (*stems)[index++] = strdup(s);
            }
        }
        return index;
    }

    void _initHunspell(const char *dic_path, const char *aff_path) {
        hunspell = new ::Hunspell(aff_path, dic_path);
    }

    ::Hunspell *_h() {
        if (!hunspell) {
            throw Php::Exception("Hunspell is not initialized");
        }
        return hunspell;
    }

    int _checkSpelling(const char *word) {
        return _h()->spell(word);
    }

    int _checkSpelling(const char *word, Php::Value &extras) {
        int info;
        char *root = NULL;
        int result = _h()->spell(word, &info, &root);
        extras["info"] = info;
        extras["root"] = root ? strdup(root) : NULL;
        free(root);
        return result;
    }

    bool _addDictionary(const char *dic_path) {
        return _h()->add_dic(dic_path) == 0;
    }

    void _suggest(const char *word, Php::Array &result) {
        char **suggestions = NULL;
        int count = _h()->suggest(&suggestions, word);
        for (int i = 0; i < count; ++i) {
            result[i] = suggestions[i];
        }
        _h()->free_list(&suggestions, count);
    }

    void _analyze(const char *word, Php::Array &result) {
        char **stems = NULL;
        int count = _h()->analyze(&stems, word);
        for (int i = 0; i < count; ++i) {
            result[i] = stems[i];
        }
        _h()->free_list(&stems, count);
    }

    void _stem(const char *word, Php::Array &result) {
        char **slst = NULL;
        int count = _h()->stem(&slst, word);
        for (int i = 0; i < count; ++i) {
            result[i] = slst[i];
        }
        _h()->free_list(&slst, count);
    }

    void _stem(const char *word, Php::Array &result, Php::Array stems_array) {
        char **slst = NULL, **stems = NULL;
        int stems_count = _phpArrayToCharPp(stems_array, &stems);
        int slst_count = _h()->stem(&slst, stems, stems_count);
        for (int i = 0; i < slst_count; ++i) {
            result[i] = slst[i];
        }
        _h()->free_list(&stems, stems_count);
        _h()->free_list(&slst, slst_count);
    }

    void _generate(const char *word1, const char *word2, Php::Array &result) {
        char **slst = NULL;
        int count = _h()->generate(&slst, word1, word2);
        for (int i = 0; i < count; ++i) {
            result[i] = slst[i];
        }
        _h()->free_list(&slst, count);
    }

    void _generate(const char *word, Php::Array stems_array, Php::Array &result) {
        char **slst = NULL, **stems = NULL;
        int stems_count = _phpArrayToCharPp(stems_array, &stems);
        int slst_count = _h()->generate(&slst, word, stems, stems_count);
        for (int i = 0; i < slst_count; ++i) {
            result[i] = slst[i];
        }
        _h()->free_list(&stems, stems_count);
        _h()->free_list(&slst, slst_count);
    }

};

}
