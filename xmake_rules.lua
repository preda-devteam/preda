rule("win.sdk")
    before_build (function (target) 
        local vcvars = target:toolchain("msvc"):config("vcvars")
        if vcvars.INCLUDE then
            target:add("sysincludedirs", path.splitenv(vcvars.INCLUDE))
        end
        target:add("syslinks", "kernel32", "user32", "gdi32", "winspool", "comdlg32", "advapi32")
        target:add("syslinks", "shell32", "ole32", "oleaut32", "uuid", "odbc32", "odbccp32", "comctl32")
        target:add("syslinks", "comdlg32", "setupapi", "shlwapi")
        if not is_plat("mingw") then
            target:add("syslinks", "strsafe")
        end
    end)

rule("linux.link_ipp")
    before_link(function (target)
        target:add("linkdirs", "SFC/libs/linux")
        target:add("syslinks", "pthread", "dl", "X11")
        target:add("syslinks", "ippdc", "ippac90lgc", "ippcc90lgc", "ippcc", "ippch90lgc", "ippch", "ippcp", "ippcv90lgc", "ippcv", "ippdc90lgc", "ippdi90lgc", "ippe", "ippgen90lgc", "ippi90lgc", "ippi", "ippj90lgc", "ippm90lgc", "ippr90lgc", "ipps90lgc", "ippsc90lgc", "ippvc90lgc", "ipps", "ippvm", "ippcore")
    end)