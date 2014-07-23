#include "php_hunspell.h"

/**
 * Hunspell library wrapper.
 *
 * See the Hunspell docs for detailed usage information:
 * @url http://sourceforge.net/projects/hunspell/files/Hunspell/Documentation/
 */

extern "C" {
    
    PHPCPP_EXPORT void *get_module() {

        static Php::Extension extension(PhpHunspellExtension::NAME, PhpHunspellExtension::VERSION);

        Php::Class<PhpHunspellExtension::Hunspell> hunspell("Hunspell");

        /**
         *  Hunspell::__construct(string dic_path, string aff_path)
         *
         *  @param string dic_path Path to the dictionary file, e.g. "/usr/share/hunspell/en_US.dic"
         *  @param string aff_path Path to the affix file, e.g. "/usr/share/hunspell/en_US.aff"
         */
        hunspell.method("__construct", &PhpHunspellExtension::Hunspell::__construct, {
            Php::ByVal("dic_path", Php::Type::String),
            Php::ByVal("aff_path", Php::Type::String)
        });

        /**
         * Hunspell::addDictionary(string dic_path)
         *
         * @paramstring dic_path Path to the dictionary file
         *
         * @return bool false if the libhunspell compiled-in dictionary limit is exceeded (defaults to 20),
         *              true otherwise, even on dictionary read failures (that's how libhunspell works, sorry)
         */
        hunspell.method("addDictionary", &PhpHunspellExtension::Hunspell::addDictionary, {
            Php::ByVal("dic_path", Php::Type::String)
        });

        /**
         *  int Hunspell::spell(string word, [array &$extras])
         *
         *  @param string word
         *  @param &array extras Optional reference variable, returns array of:
         *                       "info": a bit mask of:
         *                              #define  SPELL_COMPOUND  (1 << 0)
         *                              #define  SPELL_FORBIDDEN (1 << 1)
         *                              #define  SPELL_ALLCAP    (1 << 2)
         *                              #define  SPELL_NOCAP     (1 << 3)
         *                              #define  SPELL_INITCAP   (1 << 4)
         *                              #define  SPELL_ORIGCAP   (1 << 5)
         *                              #define  SPELL_WARN      (1 << 6)
         *                       "root": the root word of the input word.
         *                              NULL if input word is not matched OR if input word equals the root word.
         *
         *  @return int non-zero, if the input word is recognised by the spell checker, and a zero value
         *          if not.  The non-zero return value is 2 for the dictionary words with the flag "WARN"
         *          (probably bad words)
         */
        hunspell.method("spell", &PhpHunspellExtension::Hunspell::spell, {
            Php::ByVal("word", Php::Type::String),
            Php::ByRef("extras", Php::Type::Null, false)
        });

        /**
         * array Hunspell::suggest(string word)
         *
         * @param string word
         * @return array of suggestions
         */
        hunspell.method("suggest", &PhpHunspellExtension::Hunspell::suggest, {
            Php::ByVal("word", Php::Type::String)
        });

        /**
         * array Hunspell::analyze(string word)
         *
         * @param string word
         * @return array of analyze results
         */
        hunspell.method("analyze", &PhpHunspellExtension::Hunspell::analyze, {
            Php::ByVal("word", Php::Type::String)
        });

        /**
         * array Hunspell::stem(string word, [array analyze_results])
         *
         * @param string word
         * @param optional array of analyze() results
         * @return array of stems
         */
        hunspell.method("stem", &PhpHunspellExtension::Hunspell::stem, {
            Php::ByVal("word", Php::Type::String),
            Php::ByVal("analyze_results", Php::Type::Array, false)
        });

        /**
         * array Hunspell::generate(string word1, string word2)
         *
         * @param string word1
         * @param string word2
         * @return array 
         */
        hunspell.method("generate", &PhpHunspellExtension::Hunspell::generate, {
            Php::ByVal("word1", Php::Type::String),
            Php::ByVal("word2", Php::Type::String)
        });

        /**
         * array Hunspell::generateEx(string word1, array analyze_results)
         *
         * @param string word1
         * @param array  of analyze() results
         * @return array 
         */
        hunspell.method("generateEx", &PhpHunspellExtension::Hunspell::generateEx, {
            Php::ByVal("word", Php::Type::String),
            Php::ByVal("analyze_results", Php::Type::Array)
        });

        hunspell.method("getDictionaryEncoding", &PhpHunspellExtension::Hunspell::getDictionaryEncoding);
        hunspell.method("getWordChars", &PhpHunspellExtension::Hunspell::getWordChars);

#ifdef HUNSPELL_EXPERIMENTAL
        hunspell.method("suggestAuto", &PhpHunspellExtension::Hunspell::suggestAuto, {
            Php::ByVal("word", Php::Type::String),
        });

        hunspell.method("suggestPosStems", &PhpHunspellExtension::Hunspell::suggestPosStems, {
            Php::ByVal("word", Php::Type::String),
        });
#endif

        extension.add(std::move(hunspell));
        
        return extension;

    }
}
