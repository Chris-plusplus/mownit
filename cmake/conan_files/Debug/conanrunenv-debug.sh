script_folder="C:\studia\mownit\cmake\conan_files\Debug"
echo "echo Restoring environment" > "$script_folder\deactivate_conanrunenv-debug.sh"
for v in OPENSSL_MODULES OpenBLAS_HOME
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder\deactivate_conanrunenv-debug.sh"
    else
        echo unset $v >> "$script_folder\deactivate_conanrunenv-debug.sh"
    fi
done


export OPENSSL_MODULES="C:\Users\Chris\.conan2\p\b\opens8f174bc010936\p\lib\ossl-modules"
export OpenBLAS_HOME="C:\Users\Chris\.conan2\p\b\openbec6c90876f147\p"