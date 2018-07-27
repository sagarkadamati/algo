. $([IO.Path]::combine("$Home", "Workspace", "Projects", "algos", "ps1", "Common", "PSPaths.ps1"))

. PSLoadCommon.ps1
. PSLoadPlatform.ps1

STheme "Day"

# if ($Host.UI.RawUI.BackgroundColor -eq "White")
# {
# 	STheme "Day"
# }
# else
# {
# 	STheme "Night"
# }