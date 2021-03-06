#include "bongqt_export.hpp"

#include "translatableqt.hpp"
#include "filetypeqt.hpp"
#include "globalsqt.hpp"

extern "C"
{
    #include <translatable.h>
}

TranslatableQt::TranslatableQt(FileTypeQt *fileType)
{
    m_fileType = fileType;
    m_translatable = translatable_new();
    translatable_init (m_translatable, fileType->getPointer());
}

TranslatableQt::~TranslatableQt()
{
    translatable_destroy (m_translatable);
}

void TranslatableQt::init()
{
    g_type_init();
}

void TranslatableQt::readFile(QString fileName, QString locale)
{
    gchar *file_name, *_locale;
    file_name = qstringToGchar(fileName);
    _locale = qstringToGchar(locale);
    translatable_read_file (m_translatable, file_name, _locale);
    g_free(file_name);
    g_free(_locale);
}

void TranslatableQt::writeFile(QString fileName, QString locale)
{
    gchar *file_name, *_locale;
    file_name = qstringToGchar(fileName);
    _locale = qstringToGchar(locale);
    translatable_write_file (m_translatable, file_name, _locale);
    g_free(file_name);
    g_free(_locale);
}

void TranslatableQt::readContents(QString contents, QString locale)
{
    gchar *input_contents, *_locale;
    input_contents = qstringToGchar(contents);
    _locale = qstringToGchar(locale);
    translatable_read_contents (m_translatable, input_contents, _locale);
    g_free(input_contents);
    g_free(_locale);
}

QString TranslatableQt::writeContents(QString contents, QString locale)
{
    gchar *input_contents, *output_contents, *_locale;
    input_contents = qstringToGchar(contents);
    _locale = qstringToGchar(locale);
    output_contents = translatable_write_contents (m_translatable, input_contents, _locale);
    g_free(input_contents);
    g_free(_locale);
    QString toReturn = QString::fromUtf8(output_contents);
    g_free(output_contents);
    return toReturn;
}

void TranslatableQt::addEntry(QString uik, EntryIndex entryNumber, QString note, QString locale, QString string)
{
    gchar *_uik, *_note, *_locale, *_string;
    _uik = qstringToGchar(uik);
    _note = qstringToGchar(note);
    _locale = qstringToGchar(locale);
    _string = qstringToGchar(string);

    translatable_add_entry (m_translatable, entryNumber, _uik, _note, _locale, _string);

    g_free(_uik);
    g_free(_note);
    g_free(_locale);
    g_free(_string);
}

QString TranslatableQt::getNoteForUik(QString uik)
{
    gchar *_uik, *_output;
    _uik = qstringToGchar(uik);

    _output = translatable_get_note_for_uik (m_translatable, _uik);
    QString toReturn = QString::fromUtf8(_output);
    return toReturn;
}

void TranslatableQt::setNoteForUik(QString uik, QString note)
{
    gchar *_uik, *_note;
    _uik = qstringToGchar(uik);
    _note = qstringToGchar(note);

    translatable_set_note_for_uik (m_translatable, _uik, _note);

    g_free(_uik);
    g_free(_note);
}

QString TranslatableQt::getNoteForEntryIndex(EntryIndex entryNumber)
{
    gchar *_output;
    _output = translatable_get_note_for_entry_index(m_translatable, entryNumber);
    QString toReturn = QString::fromUtf8(_output);
    return toReturn;
}

void TranslatableQt::setNoteForEntryIndex(EntryIndex entryNumber, QString note)
{
    gchar *_note;
    _note = qstringToGchar(note);

    translatable_set_note_for_entry_index (m_translatable, entryNumber, _note);

    g_free(_note);
}

QString TranslatableQt::getUikForEntryIndex(EntryIndex entryNumber)
{
    gchar *_output;
    _output = translatable_get_uik_for_entry_index (m_translatable, entryNumber);
    QString toReturn = QString::fromUtf8(_output);
    return toReturn;
}

EntryIndex TranslatableQt::getEntryIndexForUik(QString uik)
{
    EntryIndex entryNumber;
    gchar *_uik;
    _uik = qstringToGchar(uik);

    entryNumber = translatable_get_entry_index_for_uik (m_translatable, _uik);

    g_free(_uik);
    return entryNumber;
}

void TranslatableQt::setEntryIndexForUik(QString uik, EntryIndex entryNumber)
{
    gchar *_uik;
    _uik = qstringToGchar(uik);

    translatable_set_entry_index_for_uik (m_translatable, _uik, entryNumber);

    g_free(_uik);
}

QString TranslatableQt::getStringForUik(QString uik, QString locale)
{
    gchar *_output, *_uik, *_locale;
    _uik = qstringToGchar(uik);
    _locale = qstringToGchar(locale);

    _output = translatable_get_string_for_uik (m_translatable, _uik, _locale);

    QString toReturn = QString::fromUtf8(_output);
    g_free(_uik);
    g_free(_locale);
    return toReturn;
}

void TranslatableQt::setStringForUik(QString uik, QString locale, QString string)
{
    gchar *_uik, *_locale, *_string;
    _uik = qstringToGchar(uik);
    _locale = qstringToGchar(locale);
    _string = qstringToGchar(string);

    translatable_set_string_for_uik (m_translatable, _uik, _locale, _string);

    g_free(_uik);
    g_free(_locale);
    g_free(_string);
}

QString TranslatableQt::getStringForEntryIndex(EntryIndex entryNumber, QString locale)
{
    gchar *_output, *_locale;
    _locale = qstringToGchar(locale);

    _output = translatable_get_string_for_entry_index (m_translatable, entryNumber, _locale);

    QString toReturn = QString::fromUtf8(_output);
    g_free(_locale);
    return toReturn;
}

void TranslatableQt::setStringForEntryIndex(EntryIndex entryNumber, QString locale, QString string)
{
    gchar *_locale, *_string;
    _locale = qstringToGchar(locale);
    _string = qstringToGchar(string);

    translatable_set_string_for_entry_index (m_translatable, entryNumber, _locale, _string);

    g_free(_locale);
    g_free(_string);
}

int TranslatableQt::entryCount()
{
    return translatable_get_entries_count (m_translatable);
}