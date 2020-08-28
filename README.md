# OmicronTK_lua

O OmicronTK_lua (Omicron Toolkit - Lua) é uma biblioteca *wrapper* simples para **Lua** e **LuaJIT**, escrito em C++ 14 para **Linux** e **Windows**.

## Compilação

O **CMake** é utilizado para a compilação.

#### Criar diretório para o build

Crie um diretório chamado **build** e depois entre nele:

```shell
mkdir build
# E depois:
cd build
```

#### Compilar usando LuaJIT instalado no sistema

```shell
cmake ..
```

Depois:

```shell
make
```

#### Compilar usando Lua instalado no sistema

```shell
cmake -DUSE_LUAJIT=OFF ..
```

Depois:

```shell
make
```

#### Compilar usando uma biblioteca personalizada de Lua ou LuaJIT

```shell
cmake -DUSE_CUSTOM_LUA=ON -DLUA_INCLUDE_DIR="/caminho/para/lua" -DLUA_LIBRARIES="/caminho/para/lua/liblua.so" ..
```

Depois:

```shell
make
```

### Opções para o CMake

#### Opções padrão:

Por padrão, a compilação utilizará o LuaJIT (```USE_LUAJIT=ON```) instalado no Sistema Operacional (```USE_CUSTOM_LUA=OFF```).

#### Usar uma biblioteca personalizada:

```shell
-DUSE_CUSTOM_LUA=ON
```

Nota: Necessário definir ```LUA_INCLUDE_DIR``` e ```LUA_LIBRARIES```

#### Caminho para os headers de Lua ou LuaJIT:

```shell
-DLUA_INCLUDE_DIR="/caminho/para/lua"
```

#### Caminho (incluindo a bliblioteca) de Lua ou LuaJIT:

```shell
-DLUA_LIBRARIES="/caminho/para/lua/liblua.so"
```

Nota: Necessário incluir a biblioteca **liblua.so**.

#### Não usar LuaJIT:

```shell
-DUSE_LUAJIT=OFF
```

Essa opção será ignorada, caso use ```-DUSE_CUSTOM_LUA=ON```

## Licença

 MIT License
 
