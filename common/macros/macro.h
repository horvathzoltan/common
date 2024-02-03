#ifndef COM_ZMACRO_H
#define COM_ZMACRO_H

#include <QRegularExpression>


#define GET(v, name) const decltype(v)& name() const {return v;}
#define SET(v, name) void name(const decltype(v)& m) {v = m;}
#define SET_UI(v, name, setui) void name(const decltype(v)& m) {v = m; setui();}

// #define zforeach(var, container) for(auto (var) = (container).begin(); (var) != (container).end(); ++(var))
// #define zforeach_from(var, container, ix) for(auto (var) = (container).begin()+(ix); (var) != (container).end(); ++(var))

#endif // ZMACRO_H
