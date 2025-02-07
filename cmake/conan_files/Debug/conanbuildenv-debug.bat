@echo off
chcp 65001 > nul
setlocal
echo @echo off > "%~dp0/deactivate_conanbuildenv-debug.bat"
echo echo Restoring environment >> "%~dp0/deactivate_conanbuildenv-debug.bat"
for %%v in (OpenBLAS_HOME) do (
    set foundenvvar=
    for /f "delims== tokens=1,2" %%a in ('set') do (
        if /I "%%a" == "%%v" (
            echo set "%%a=%%b">> "%~dp0/deactivate_conanbuildenv-debug.bat"
            set foundenvvar=1
        )
    )
    if not defined foundenvvar (
        echo set %%v=>> "%~dp0/deactivate_conanbuildenv-debug.bat"
    )
)
endlocal


set "OpenBLAS_HOME=C:\Users\Chris\.conan2\p\b\openbec6c90876f147\p"