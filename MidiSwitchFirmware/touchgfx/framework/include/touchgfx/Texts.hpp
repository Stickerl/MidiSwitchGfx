/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef TEXTS_HPP
#define TEXTS_HPP

#include <touchgfx/Unicode.hpp>

namespace touchgfx
{
/**
 * @typedef uint16_t LanguageId
 *
 * @brief Language IDs generated by the text converter are uint16_t typedef'ed.
 */
typedef uint16_t LanguageId;

/**
 * @class Texts Texts.hpp touchgfx/Texts.hpp
 *
 * @brief Class for setting language and getting texts.
 *
 *        Class for setting language and getting texts. The language set will determine which
 *        texts will be used.
 */
class Texts
{
public:

    /**
     * @fn static void Texts::setLanguage(LanguageId id);
     *
     * @brief Sets the current language for texts.
     *
     *        Sets the current language for texts.
     *
     * @param id The id of the language.
     */
    static void setLanguage(LanguageId id);

    /**
     * @fn static LanguageId Texts::getLanguage()
     *
     * @brief Gets the current language.
     *
     *        Gets the current language.
     *
     * @return The id of the language.
     */
    static LanguageId getLanguage()
    {
        return currentLanguage;
    }

    /**
     * @fn const Unicode::UnicodeChar* Texts::getText(TypedTextId id) const
     *
     * @brief Get text in the set language.
     *
     *        Get text in the set language.
     *
     * @param id The id of the text to lookup.
     *
     * @return The text.
     */
    const Unicode::UnicodeChar* getText(TypedTextId id) const
    {
        return currentLanguagePtr[id];
    }

private:
    static const Unicode::UnicodeChar* const* currentLanguagePtr;
    static LanguageId currentLanguage;
};

} // namespace touchgfx

#endif // TEXTS_HPP
