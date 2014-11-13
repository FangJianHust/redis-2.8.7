/*
* all.c -- Lua core, libraries and interpreter in a single file
*/

#define luaall_c

#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lapi.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lcode.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/ldebug.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/ldo.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/ldump.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lfunc.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lgc.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/llex.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lmem.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lobject.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lopcodes.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lparser.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lstate.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lstring.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/ltable.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/ltm.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lundump.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lvm.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lzio.c"

#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lauxlib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lbaselib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/ldblib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/liolib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/linit.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lmathlib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/loadlib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/loslib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lstrlib.c"
#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/ltablib.c"

#include "/home/fangjian/c++project/redis-2.8.7/deps/lua/src/lua.c"
