import (
    "strings"
    "strconv"
)

func validIPAddress(IP string) string {

    // valid char
    for _, c := range IP {
        if !(c>='0' && c<='9' || c>='A'&& c<='F' ||  c>='a'&& c<='f' || c=='.' || c==':') {
            return "Neither"
        }
    }

    if parts := strings.Split(IP, "."); len(parts)==4 {
        for _, p := range parts {
            if val, err := strconv.Atoi(p); len(p)==0 || err != nil || len(p)>1 && p[0]=='0' || val>255 {
                return "Neither"
            }
        }
        return "IPv4"
    }

    if parts := strings.Split(IP, ":"); len(parts)==8{
        for _, p := range parts{
            if len(p)==0 || len(p)>4 {
            return "Neither"
            }
        }
        return "IPv6"
    }
    return "Neither"
}