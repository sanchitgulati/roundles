#include "LocalizedString.h"

using namespace std;

LocalizedString::LocalizedString() {
}

LocalizedString::~LocalizedString() {
}

__String* LocalizedString::localizedString(const char *key){

    const char* fileName;
    auto val = UserDefault::getInstance()->getStringForKey("language", "Base");
    if(val.compare("Base"))
    {
        fileName = val.c_str();
    }
    else
    {
        fileName = getSystemLang();
    }
    __String* str;

    string fname = fileName;
    fname = fname + "/LocalizedString.plist";

    __Dictionary* language = __Dictionary::createWithContentsOfFile(fname.c_str());

    str = (__String *) language->objectForKey(key);

    if (str == NULL) {
        str = __String::create(key);
    }

    return str;
}

const char* LocalizedString::getSystemLang()
{
    LanguageType curLanguage = Application::getInstance()->getCurrentLanguage();

    switch (curLanguage) {
        case LanguageType::ENGLISH:
            return "en.lproj";
            break;
        case LanguageType::JAPANESE:
            return "ja.lproj";
            break;
        case LanguageType::GERMAN:
            return "de.lproj";
            break;
        case LanguageType::FRENCH:
            return "fr.lproj";
            break;
        default:
            return "en.lproj";
            break;
    }
}
