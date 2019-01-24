function Install-KeyHandlers {
	Set-PSReadlineKeyHandler -Key "Ctrl+f"           -Function ForwardChar
	Set-PSReadlineKeyHandler -Key "Ctrl+Alt+f"       -Function ForwardWord
	Set-PSReadlineKeyHandler -Key "Ctrl+Shift+f"     -Function SelectForwardChar
	Set-PSReadlineKeyHandler -Key "Ctrl+Shift+Alt+f" -Function SelectForwardWord

	Set-PSReadlineKeyHandler -Key "Ctrl+b"           -Function BackwardChar
	Set-PSReadlineKeyHandler -Key "Ctrl+Alt+b"       -Function BackwardWord
	Set-PSReadlineKeyHandler -Key "Ctrl+Shift+b"     -Function SelectBackwardChar
	Set-PSReadlineKeyHandler -Key "Ctrl+Shift+Alt+b" -Function SelectBackwardWord

	Set-PSReadlineKeyHandler -Key "Ctrl+a"           -Function BeginningOfLine
	Set-PSReadlineKeyHandler -Key "Ctrl+e"           -Function EndOfLine
	Set-PSReadlineKeyHandler -Key "Ctrl+Shift+e"     -Function SelectLine
	Set-PSReadlineKeyHandler -Key "Ctrl+Shift+Alt+a" -Function SelectBackwardsLine

	Set-PSReadlineKeyHandler -Key "Ctrl+d"           -Function DeleteChar
	Set-PSReadlineKeyHandler -Key "Ctrl+Alt+d"       -Function KillWord
	Set-PSReadlineKeyHandler -Key "Ctrl+k"           -Function KillLine

	Set-PSReadlineKeyHandler -Key "Ctrl+n"           -Function HistorySearchForward
	Set-PSReadlineKeyHandler -Key "Ctrl+p"           -Function HistorySearchBackward

	if ([System.Environment]::OSVersion.Platform -eq "Win32NT") {
		Set-PSReadlineKeyHandler -Key "Ctrl+Alt+p"   -Function ScrollDisplayUp
		Set-PSReadlineKeyHandler -Key "Ctrl+Alt+n"   -Function ScrollDisplayDown
	}
}

# Export-ModuleMember -Function Install-KeyHandlers