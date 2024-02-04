#ifndef STRINGLITERAL2_H
#define STRINGLITERAL2_H

#define QL(str) \
    ([]() noexcept -> QString { \
        enum { Size = sizeof(QT_UNICODE_LITERAL(str))/2 - 1 }; \
        static const QStaticStringData<Size> qstring_literal = { \
            Q_STATIC_STRING_DATA_HEADER_INITIALIZER(Size), \
            QT_UNICODE_LITERAL(str) }; \
        QStringDataPtr holder = { qstring_literal.data_ptr() }; \
        return QString(holder); \
    }()) \
    /**/

#endif // STRINGLITERAL2_H
