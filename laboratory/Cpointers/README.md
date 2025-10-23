
# Tutorial de C - Punteros Completo

Este repositorio contiene una colección de tutoriales de C enfocados en punteros y conceptos relacionados. El proyecto ha sido configurado para usar con Visual Studio Code y `gcc` tanto en Windows como en macOS.

## Prerequisitos

### Para Usuarios de Windows
1. Visual Studio Code  
2. Extensión **C/C++** para VSCode  
3. **MinGW-w64** (para gcc)  
   - Descarga e instala desde: https://www.msys2.org/  
   - Después de instalar, abre MSYS2 y ejecuta:
     ```bash
     pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb
     ```
   - Asegúrate de agregar la ruta del compilador al PATH (típicamente `C:\msys64\mingw64\bin`)

### Para Usuarios de macOS
1. Visual Studio Code  
2. Extensión **C/C++** para VSCode  
3. GCC (instalar vía Homebrew)
   ```bash
   brew install gcc
   ```
   Esto instalará la última versión de gcc (actualmente gcc-14 o similar)

## Estructura del Proyecto

```
proyecto/
├── 0_Cpointers/                 - Conceptos básicos de punteros
│   ├── 1_Pointers.c              - Código fuente en C
│   └── build/                  - Directorio de compilación (generado automáticamente)
│       └── Pointers            - Ejecutable (generado al compilar)
└── ... otros directorios
```

Cada tutorial está en su propio directorio y al compilarse, se crea automáticamente una carpeta `build/` que contiene los ejecutables. Esta carpeta `build/` está excluida de git para mantener limpio el repositorio.

## Compilación y Ejecución

### Usando VSCode

#### Compilar y Ejecutar (Sin Depuración)
1. Abre la carpeta del tutorial en VSCode  
2. Abre el archivo `.c` que deseas ejecutar  
3. Presiona `Ctrl+Shift+B` (Windows) o `Cmd+Shift+B` (macOS) para compilar  
4. Para ejecutar, presiona `Ctrl+Shift+P` (Windows) o `Cmd+Shift+P` (macOS), selecciona "Run Task", luego elige "C: Run Program"

#### Depurar el Programa
1. Abre el archivo `.c` que deseas depurar  
2. Establece puntos de interrupción haciendo clic en el margen izquierdo  
3. Presiona `F5` para iniciar la depuración  
4. Usa los controles para avanzar paso a paso, continuar, etc.

El sistema:
- Creará automáticamente una carpeta `build/` en el directorio del archivo fuente  
- Compilará con símbolos de depuración (`-g`) y colocará el ejecutable allí  
- Utilizará `gdb` en Windows o `lldb` en macOS según el sistema operativo

## Extensiones Recomendadas para VSCode

Para una mejor experiencia de desarrollo en C:

- [C/C++ Extension Pack (Microsoft)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)  
  Incluye:
  - IntelliSense para C
  - Depuración con gdb/lldb
  - Explorador de símbolos
  - Formateo automático de código y más

### Compilación Manual (Alternativa)

Si prefieres usar la terminal directamente:

#### En Windows
```bash
cd <directorio_del_ejemplo>
mkdir build
gcc -g archivo.c -o build/archivo.exe && ./build/archivo.exe
```

#### En macOS
```bash
cd <directorio_del_ejemplo>
mkdir -p build
gcc-14 -g archivo.c -o build/archivo && ./build/archivo
```

> ⚠️ Asegúrate de que el archivo fuente tenga extensión `.c`

## Estructura de Archivos de Configuración

### `.vscode/tasks.json`
Define tareas para:
- Compilar programas en C con símbolos de depuración (`-g`)
- Ejecutar programas compilados sin depuración

### `.vscode/launch.json`
Define configuraciones para:
- Depurar programas en C con `gdb` (Windows) o `lldb` (macOS)

### `.gitignore`
- Excluye todas las carpetas `build/` en cualquier parte del proyecto  
- Ignora archivos objeto (`*.o`, `*.obj`) y ejecutables (`*.exe`, `*.out`)  
- Mantiene limpio el repositorio

## Solución de Problemas

### Problemas Comunes
1. **gcc no funciona**:
   - Windows: Verifica que MinGW esté en el `PATH` (`C:\msys64\mingw64\bin`)
   - macOS: Verifica que gcc esté instalado (`brew list | grep gcc`)

2. **Errores de compilación**:
   - Verifica que estés en el directorio correcto
   - Asegúrate de que el archivo tenga extensión `.c` y esté bien escrito

3. **VSCode no detecta el compilador**:
   - Reinicia VSCode después de instalar o configurar MinGW/gcc
   - macOS: Verifica que la ruta a `gcc-14` esté en el `PATH` (usualmente `/opt/homebrew/bin`)

4. **La depuración no funciona**:
   - Asegúrate de compilar con `-g`
   - macOS: Verifica que `lldb` esté instalado y autorizado
   - Windows: Asegúrate de que `gdb` esté instalado con `pacman -S mingw-w64-x86_64-gdb`

5. **No se crea la carpeta `build/`**:
   - Verifica que tengas permisos en el directorio
   - Intenta crearla manualmente si es necesario
