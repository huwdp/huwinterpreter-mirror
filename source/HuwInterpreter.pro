TARGET = HuwInterpreter
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

CONFIG += c++14
CONFIG += -j6
LIBS += -lcurl
LIBS += -lreadline

CONFIG += warn_off

#QMAKE_CXXFLAGS += -Wall
#QMAKE_CXXFLAGS += -Wextra

#QMAKE_CXXFLAGS += -Wlogical-op
#QMAKE_CXXFLAGS += -Wuseless-cast
#QMAKE_CXXFLAGS += -Wdouble-promotion
#QMAKE_CXXFLAGS += -Wformat=2
#QMAKE_CXXFLAGS += -Wunused-function
#QMAKE_CXXFLAGS += -Wunused-variable

QMAKE_CXXFLAGS_RELEASE += -fno-rtti
QMAKE_CXXFLAGS_RELEASE += -fmerge-all-constants
QMAKE_CXXFLAGS_RELEASE += -O2
-QMAKE_CXXFLAGS_RELEASE += -pipe

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-function
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-variable

SOURCES += \
    errors/debug.cpp \
    errors/error.cpp \
    errors/errors.cpp \
    errors/errortypestringfactory.cpp \
    functions/httpdeletefunction.cpp \
    functions/httpgetfunction.cpp \
    functions/httpheadfunction.cpp \
    functions/httppostfunction.cpp \
    functions/httpputfunction.cpp \
    functions/jsondecodefunction.cpp \
    functions/jsonencodefunction.cpp \
    functions/lround.cpp \
    functions/sleepfunction.cpp \
    functions/sort.cpp \
    io/fileline.cpp \
    io/io.cpp \
    nodes/importnode.cpp \
    tokens/tokenlist.cpp \
    tokens/unusabletokenlist.cpp \
    types/typedetector.cpp \
    variables/precision.cpp \
    variables/scope.cpp \
    variables/variable.cpp \
    variables/variables.cpp \
    variables/variabletypefactory.cpp \
    huwinterpreter.cpp \
    functions/customfunction.cpp \
    functions/emptyfunction.cpp \
    variables/doublevariable.cpp \
    variables/stringvariable.cpp \
    variables/hashtablevariable.cpp \
    functions/array.cpp \
    functions/arrayunset.cpp \
    functions/count.cpp \
    variables/constantvariable.cpp \
    functions/isarraytype.cpp \
    functions/isdoubletype.cpp \
    functions/isnumbertype.cpp \
    functions/isinttype.cpp \
    functions/isstringtype.cpp \
    functions/isint.cpp \
    functions/isdouble.cpp \
    functions/todouble.cpp \
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
    functions/exp.cpp \
    functions/fileread.cpp \
    functions/filewrite.cpp \
    functions/floor.cpp \
    functions/function.cpp \
    functions/functions.cpp \
    functions/instr.cpp \
    functions/instrrev.cpp \
    functions/isnumber.cpp \
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
    parser/parser.cpp \
    tokens/filetokenmanager.cpp \
    tokens/lineinfo.cpp \
    tokens/scanner.cpp \
    tokens/texttokenmanager.cpp \
    tokens/token.cpp \
    main.cpp \
    nodes/addconstnode.cpp \
    nodes/addnode.cpp \
    nodes/addvarnode.cpp \
    nodes/bitwiseandnode.cpp \
    nodes/bitwiseornode.cpp \
    nodes/getfuncnode.cpp \
    nodes/equalnode.cpp \
    nodes/divnode.cpp \
    nodes/decrementnode.cpp \
    nodes/bracketnode.cpp \
    nodes/ifequalnode.cpp \
    nodes/ifnode.cpp \
    nodes/ifandnode.cpp \
    nodes/huwcodenodefactory.cpp \
    nodes/getvarnode.cpp \
    nodes/ifnotequalnode.cpp \
    nodes/ifornode.cpp \
    nodes/ifovernode.cpp \
    nodes/ifoverorequalnode.cpp \
    nodes/ifundernode.cpp \
    nodes/ifunderorequalnode.cpp \
    nodes/numbernode.cpp \
    nodes/mulnode.cpp \
    nodes/modnode.cpp \
    nodes/incrementnode.cpp \
    nodes/runnode.cpp \
    nodes/setreturnnode.cpp \
    nodes/setvarnode.cpp \
    nodes/subnode.cpp \
    nodes/textnode.cpp \
    nodes/unaryminusnode.cpp \
    nodes/whilenode.cpp \
    nodes/unarynotnode.cpp \
    nodes/nodefactoryfactory.cpp \
    nodes/semicolonnode.cpp \
    format/escapecharacteroutput.cpp \
    common/passable.cpp \
    errors/errorfactory.cpp \
    functions/fileexists.cpp \
    functions/regexsearch.cpp \
    functions/regexmatch.cpp \
    functions/regexreplace.cpp \
    nodes/bitwisexornode.cpp \
    nodes/bitwisecomplementnode.cpp \
    nodes/leftshiftnode.cpp \
    nodes/rightshiftnode.cpp \
    variables/variablestringfactory.cpp \
    nodes/arraygetnode.cpp \
    errors/stacktracemanager.cpp \
    errors/stacktrace.cpp \
    common/nameableobject.cpp \
    nodes/arraysetnode.cpp \
    variables/refvariable.cpp \
    functions/reffunction.cpp \
    functions/currenttimefunction.cpp \
    functions/clockfunction.cpp \
    functions/dirfunction.cpp \
    functions/timeformatfunction.cpp \
    functions/unreffunction.cpp \
    functions/tonumber.cpp




HEADERS += \
    errors/debug.h \
    errors/error.h \
    errors/errors.h \
    errors/errortypes.h \
    errors/errortypestringfactory.h \
    errors/ierrors.h \
    functions/asort.h \
    functions/httpdeletefunction.h \
    functions/httpgetfunction.h \
    functions/httpheadfunction.h \
    functions/httppostfunction.h \
    functions/httpputfunction.h \
    functions/jsondecodefunction.h \
    functions/jsonencodefunction.h \
    functions/lround.h \
    functions/sleepfunction.h \
    functions/sort.h \
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
    nodes/importnode.h \
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
    tokens/tokenlist.h \
    tokens/tokenmanager.h \
    tokens/unusabletokenlist.h \
    types/isnumeric.h \
    types/tokentypes.h \
    types/typedetector.h \
    variables/precision.h \
    variables/scope.h \
    variables/variable.h \
    variables/variables.h \
    variables/variabletypefactory.h \
    huwinterpreter.h \
    nodes/setreturnnode.h \
    nodes/incrementnode.h \
    nodes/decrementnode.h \
    variables/doublevariable.h \
    variables/hashtablevariable.h \
    variables/stringvariable.h \
    functions/array.h \
    variables/constantvariable.h \
    tokens/tokenmanager.h \
    nodes/unaryminusnode.h \
    nodes/unarynotnode.h \
    nodes/bitwiseandnode.h \
    nodes/bitwiseornode.h \
    functions/isdoubletype.h \
    functions/isinttype.h \
    functions/isnumbertype.h \
    functions/isint.h \
    functions/isdouble.h \
    functions/isnumber.h \
    nodes/addconstnode.h \
    nodes/addvarnode.h \
    nodes/huwcodenodefactory.h \
    nodes/nodefactory.h \
    functions/abs.h \
    functions/acos.h \
    functions/arrayunset.h \
    functions/asc.h \
    functions/asin.h \
    functions/atan.h \
    functions/atan2.h \
    functions/ceil.h \
    functions/cha.h \
    functions/command.h \
    functions/cos.h \
    functions/count.h \
    functions/customfunction.h \
    functions/emptyfunction.h \
    functions/exp.h \
    functions/fileread.h \
    functions/filewrite.h \
    functions/floor.h \
    functions/function.h \
    functions/functionlist.h \
    functions/functions.h \
    functions/instr.h \
    functions/instrrev.h \
    functions/isarraytype.h \
    functions/isstringtype.h \
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
    functions/todouble.h \
    functions/tolower.h \
    functions/tostring.h \
    functions/toupper.h \
    functions/trim.h \
    functions/weekday.h \
    functions/weekdayname.h \
    functions/year.h \
    nodes/addconstnode.h \
    nodes/addnode.h \
    nodes/addvarnode.h \
    nodes/bitwiseandnode.h \
    nodes/bitwiseornode.h \
    nodes/bracketnode.h \
    nodes/decrementnode.h \
    nodes/divnode.h \
    nodes/equalnode.h \
    nodes/getfuncnode.h \
    nodes/getvarnode.h \
    nodes/huwcodenodefactory.h \
    nodes/ifandnode.h \
    nodes/ifequalnode.h \
    nodes/ifnode.h \
    nodes/ifnotequalnode.h \
    nodes/ifornode.h \
    nodes/ifovernode.h \
    nodes/ifoverorequalnode.h \
    nodes/ifundernode.h \
    nodes/ifunderorequalnode.h \
    nodes/incrementnode.h \
    nodes/modnode.h \
    nodes/mulnode.h \
    nodes/node.h \
    nodes/nodefactory.h \
    nodes/numbernode.h \
    nodes/runnode.h \
    nodes/setreturnnode.h \
    nodes/setvarnode.h \
    nodes/subnode.h \
    nodes/textnode.h \
    nodes/unaryminusnode.h \
    nodes/unarynotnode.h \
    nodes/whilenode.h \
    parser/parser.h \
    types/isnumeric.h \
    types/tokentypes.h \
    nodes/nodefactoryfactory.h \
    nodes/semicolonnode.h \
    format/escapecharacteroutput.h \
    common/passable.h \
    errors/errorfactory.h \
    functions/fileexists.h \
    functions/regexsearch.h \
    functions/regexmatch.h \
    functions/regexreplace.h \
    nodes/bitwisexornode.h \
    nodes/bitwisecomplementnode.h \
    nodes/leftshiftnode.h \
    nodes/rightshiftnode.h \
    variables/variablestringfactory.h \
    nodes/arraygetnode.h \
    errors/stacktracemanager.h \
    errors/stacktrace.h \
    common/nameableobject.h \
    nodes/arraysetnode.h \
    nodes/refnode.h \
    variables/refvariable.h \
    functions/reffunction.h \
    functions/currenttimefunction.h \
    functions/clockfunction.h \
    functions/dirfunction.h \
    functions/timeformatfunction.h \
    functions/unreffunction.h \
    functions/tonumber.h

DISTFILES += \
    CMakeLists.txt \
    build.sh



