add_rules("mode.debug", "mode.release")

-- Configuration des drapeaux du compilateur
if is_plat("windows") then
    -- Configuration pour Windows
    -- /W3 : Niveau d'avertissement 3 (equivalent a -Wall en C)
    -- /W4 : Niveau d'avertissement 4 (equivalent a -Wextra en C)
    -- /permissive- : Bien que principalement un drapeau C++, peut aider à identifier des constructions ambigües
    add_cxflags("/W3", "/W4", "/permissive-", {force = true}) -- Niveaux d'avertissement et mode strict
else
    -- Configuration pour Unix-like
    -- -Wall : Active tous les avertissements de base
    -- -Wextra : Active des avertissements supplémentaires
    -- -pedantic : Enforce strictement les standards C
    -- -Wno-newline-eof : Désactive les avertissements pour les nouvelles lignes à la fin du fichier
    add_cxflags("-Wall", "-Wextra", "-pedantic", "-Wno-newline-eof", {force = true}) -- Avertissements généraux et spécifiques
end

set_project("rcenet")

if not is_plat("windows", "mingw") then
    -- detect features on Unix platforms
    option("fcntl", { cincludes = {"fcntl.h", "unistd.h"}, cfuncs = "fcntl", defines = "HAS_FCNTL=1"})
    option("poll", { cincludes = {"poll.h"}, cfuncs = "poll", defines = "HAS_POLL=1"})
    option("getaddrinfo", { cincludes = {"sys/types.h", "sys/socket.h", "netdb.h"}, cfuncs = "getaddrinfo", defines = "HAS_GETADDRINFO=1"})
    option("getnameinfo", { cincludes = {"sys/types.h", "sys/socket.h", "netdb.h"}, cfuncs = "getnameinfo", defines = "HAS_GETNAMEINFO=1"})
    option("gethostbyaddr_r", { cincludes = {"netdb.h"}, cfuncs = "gethostbyaddr_r", defines = "HAS_GETHOSTBYADDR_R=1"})
    option("gethostbyname_r", { cincludes = {"netdb.h"}, cfuncs = "gethostbyname_r", defines = "HAS_GETHOSTBYNAME_R=1"})
    option("inet_pton", { cincludes = {"arpa/inet.h"}, cfuncs = "inet_pton", defines = "HAS_INET_PTON=1"})
    option("inet_ntop", { cincludes = {"arpa/inet.h"}, cfuncs = "inet_ntop", defines = "HAS_INET_NTOP=1"})
    option("socklen_t", { cincludes = {"sys/types.h", "sys/socket.h"}, ctypes = "socklen_t", defines = "HAS_SOCKLEN_T=1"})

    option("msghdr_flags", function ()
        add_csnippets("msghdr_flags", [[
            #include <sys/socket.h>
            int get_flags(struct msghdr* m)
            { 
                return m->msg_flags;
            }]])
    end)
end

add_includedirs("include")

target("rcenet", function ()
    set_kind("$(kind)")

    add_headerfiles("include/(rcenet/*.h)")
    add_files("src/*.c")

    if is_kind("shared") then
        add_defines("ENET_DLL", { public = true })
    end

    if is_plat("windows", "mingw") then
        add_syslinks("winmm", "ws2_32", { public = true })
    -- Solaris pas pris encore en charge par xmake mais a l'avenir peut-être
    elseif is_plat("solaris") then
        add_syslinks("socket", "nsl", { public = true })
    else
        add_options(
            "fcntl",
            "poll", 
            "getaddrinfo",
            "getnameinfo",
            "gethostbyaddr_r",
            "gethostbyname_r",
            "inet_pton",
            "inet_ntop",
            "msghdr_flags",
            "socklen_t")
    end
end)