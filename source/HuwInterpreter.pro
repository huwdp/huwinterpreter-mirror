QT += core
QT -= gui

TARGET = HuwInterpreter
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

CONFIG += c++11
CONFIG += j6
CONFIG += Wunused-parameter

QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter

SOURCES += \
    errors/debug.cpp \
    errors/error.cpp \
    errors/errors.cpp \
    errors/errortypestringfactory.cpp \
    functions/abs.cpp \
    functions/acos.cpp \
    functions/asc.cpp \
    functions/asin.cpp \
    functions/atan.cpp \
    functions/atan2.cpp \
    functions/ceil.cpp \
    functions/cha.cpp \
    functions/command.cpp \
    functions/cos.cpp \
    functions/dateformat.cpp \
    functions/exp.cpp \
    functions/fileread.cpp \
    functions/filewrite.cpp \
    functions/floor.cpp \
    functions/function.cpp \
    functions/functions.cpp \
    functions/instr.cpp \
    functions/instrrev.cpp \
    functions/left.cpp \
    functions/len.cpp \
    functions/log.cpp \
    functions/ltrim.cpp \
    functions/max.cpp \
    functions/mid.cpp \
    functions/min.cpp \
    functions/month.cpp \
    functions/monthname.cpp \
    functions/not.cpp \
    functions/now.cpp \
    functions/pow.cpp \
    functions/print.cpp \
    functions/random.cpp \
    functions/replace.cpp \
    functions/right.cpp \
    functions/round.cpp \
    functions/rtrim.cpp \
    functions/scan.cpp \
    functions/sin.cpp \
    functions/space.cpp \
    functions/sqrt.cpp \
    functions/str.cpp \
    functions/strcomp.cpp \
    functions/strreverse.cpp \
    functions/tan.cpp \
    functions/tolower.cpp \
    functions/tostring.cpp \
    functions/toupper.cpp \
    functions/trim.cpp \
    functions/weekday.cpp \
    functions/weekdayname.cpp \
    functions/year.cpp \
    io/fileline.cpp \
    io/io.cpp \
    nodes/addnode.cpp \
    nodes/bracketnode.cpp \
    nodes/divnode.cpp \
    nodes/equalnode.cpp \
    nodes/getfuncnode.cpp \
    nodes/getvarnode.cpp \
    nodes/ifandnode.cpp \
    nodes/ifequalnode.cpp \
    nodes/ifnode.cpp \
    nodes/ifnotequalnode.cpp \
    nodes/ifornode.cpp \
    nodes/ifovernode.cpp \
    nodes/ifoverorequalnode.cpp \
    nodes/ifundernode.cpp \
    nodes/ifunderorequalnode.cpp \
    nodes/modnode.cpp \
    nodes/mulnode.cpp \
    nodes/numbernode.cpp \
    nodes/runnode.cpp \
    nodes/setvarnode.cpp \
    nodes/subnode.cpp \
    nodes/textnode.cpp \
    nodes/whilenode.cpp \
    parser/parser.cpp \
    tokens/filetokenmanager.cpp \
    tokens/lineinfo.cpp \
    tokens/scanner.cpp \
    tokens/texttokenmanager.cpp \
    tokens/token.cpp \
    tokens/tokendetector.cpp \
    types/isnumeric.cpp \
    types/typedetector.cpp \
    variables/precision.cpp \
    variables/scope.cpp \
    variables/variable.cpp \
    variables/variables.cpp \
    variables/variabletypefactory.cpp \
    huwinterpreter.cpp \
    main.cpp \
    functions/customfunction.cpp \
    functions/emptyfunction.cpp \
    nodes/returnnode.cpp \
    nodes/setreturnnode.cpp \
    nodes/incrementnode.cpp \
    nodes/decrementnode.cpp \
    variables/doublevariable.cpp \
    variables/integervariable.cpp \
    variables/numbervariable.cpp \
    variables/stringvariable.cpp \
    variables/hashtablevariable.cpp \
    functions/arrayget.cpp \
    functions/arrayset.cpp \
    functions/array.cpp \
    functions/arrayunset.cpp \
    functions/count.cpp

HEADERS += \
    errors/debug.h \
    errors/error.h \
    errors/errors.h \
    errors/errortypes.h \
    errors/errortypestringfactory.h \
    errors/ierrors.h \
    functions/abs.h \
    functions/acos.h \
    functions/asc.h \
    functions/asin.h \
    functions/atan.h \
    functions/atan2.h \
    functions/ceil.h \
    functions/cha.h \
    functions/command.h \
    functions/cos.h \
    functions/dateformat.h \
    functions/exp.h \
    functions/fileread.h \
    functions/filewrite.h \
    functions/floor.h \
    functions/function.h \
    functions/functionlist.h \
    functions/functions.h \
    functions/instr.h \
    functions/instrrev.h \
    functions/left.h \
    functions/len.h \
    functions/log.h \
    functions/ltrim.h \
    functions/max.h \
    functions/mid.h \
    functions/min.h \
    functions/month.h \
    functions/monthname.h \
    functions/not.h \
    functions/now.h \
    functions/pow.h \
    functions/print.h \
    functions/random.h \
    functions/replace.h \
    functions/right.h \
    functions/round.h \
    functions/rtrim.h \
    functions/scan.h \
    functions/sin.h \
    functions/space.h \
    functions/sqrt.h \
    functions/str.h \
    functions/strcomp.h \
    functions/strreverse.h \
    functions/tan.h \
    functions/tolower.h \
    functions/tostring.h \
    functions/toupper.h \
    functions/trim.h \
    functions/weekday.h \
    functions/weekdayname.h \
    functions/year.h \
    io/fileline.h \
    io/io.h \
    nodes/addnode.h \
    nodes/bracketnode.h \
    nodes/divnode.h \
    nodes/equalnode.h \
    nodes/getfuncnode.h \
    nodes/getvarnode.h \
    nodes/ifandnode.h \
    nodes/ifequalnode.h \
    nodes/ifnode.h \
    nodes/ifnotequalnode.h \
    nodes/ifornode.h \
    nodes/ifovernode.h \
    nodes/ifoverorequalnode.h \
    nodes/ifundernode.h \
    nodes/ifunderorequalnode.h \
    nodes/modnode.h \
    nodes/mulnode.h \
    nodes/node.h \
    nodes/numbernode.h \
    nodes/runnode.h \
    nodes/setvarnode.h \
    nodes/subnode.h \
    nodes/textnode.h \
    nodes/whilenode.h \
    parser/parser.h \
    tokens/filetokenmanager.h \
    tokens/lineinfo.h \
    tokens/scanner.h \
    tokens/texttokenmanager.h \
    tokens/token.h \
    tokens/tokendetector.h \
    tokens/tokenmanager.h \
    types/isnumeric.h \
    types/tokentypes.h \
    types/typedetector.h \
    variables/HashTableVariable.h \
    variables/DoubleVariable.h \
    variables/IntegerVariable.h \
    variables/NumberVariable.h \
    variables/StringVariable.h \
    variables/precision.h \
    variables/scope.h \
    variables/variable.h \
    variables/variables.h \
    variables/variabletypefactory.h \
    huwinterpreter.h \
    functions/customfunction.h \
    functions/emptyfunction.h \
    nodes/returnnode.h \
    nodes/setreturnnode.h \
    nodes/incrementnode.h \
    nodes/decrementnode.h \
    variables/doublevariable.h \
    variables/hashtablevariable.h \
    variables/stringvariable.h \
    variables/numbervariable.h \
    variables/integervariable.h \
    functions/arrayget.h \
    functions/arrayset.h \
    functions/array.h \
    functions/arrayunset.h \
    functions/count.h

