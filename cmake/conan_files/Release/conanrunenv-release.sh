script_folder="C:\studia\mownit\cmake\conan_files\Release"
echo "echo Restoring environment" > "$script_folder\deactivate_conanrunenv-release.sh"
for v in OPENSSL_MODULES OpenBLAS_HOME
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder\deactivate_conanrunenv-release.sh"
    else
        echo unset $v >> "$script_folder\deactivate_conanrunenv-release.sh"
    fi
done


export OPENSSL_MODULES="C:\Users\Chris\.conan2\p\b\opensc09aa5a637f10\p\lib\ossl-modules"
export OpenBLAS_HOME="C:\Users\Chris\.conan2\p\openb191c4c53bb898\p"