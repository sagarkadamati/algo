function Install-KeyHandlers {
	Set-PSReadlineKeyHandler -Key "Ctrl+F"           -Function ForwardChar
	Set-PSReadlineKeyHandler -Key "Shift+Ctrl+F"     -Function SelectForwardChar
	Set-PSReadlineKeyHandler -Key "Alt+Ctrl+F"       -Function ForwardWord
	Set-PSReadlineKeyHandler -Key "Alt+Shift+Ctrl+F" -Function SelectForwardWord

	Set-PSReadlineKeyHandler -Key "Ctrl+B"           -Function BackwardChar
	Set-PSReadlineKeyHandler -Key "Shift+Ctrl+B"     -Function SelectBackwardChar
	Set-PSReadlineKeyHandler -Key "Alt+Ctrl+B"       -Function BackwardWord
	Set-PSReadlineKeyHandler -Key "Alt+Shift+Ctrl+B" -Function SelectBackwardWord

	Set-PSReadlineKeyHandler -Key "Ctrl+E"           -Function EndOfLine
	Set-PSReadlineKeyHandler -Key "Shift+Ctrl+E"     -Function SelectLine
	Set-PSReadlineKeyHandler -Key "Ctrl+A"           -Function BeginningOfLine
	Set-PSReadlineKeyHandler -Key "Shift+Ctrl+A"     -Function SelectBackwardsLine

	Set-PSReadlineKeyHandler -Key "Ctrl+D"           -Function DeleteChar
	Set-PSReadlineKeyHandler -Key "Alt+Ctrl+D"       -Function KillWord
	Set-PSReadlineKeyHandler -Key "Ctrl+K"           -Function KillLine

	Set-PSReadlineKeyHandler -Key "Ctrl+N"           -Function HistorySearchForward
	Set-PSReadlineKeyHandler -Key "Ctrl+P"           -Function HistorySearchBackward

	if ([System.Environment]::OSVersion.Platform -eq "Win32NT") {
		Set-PSReadlineKeyHandler -Key "Ctrl+Alt+p"       -Function ScrollDisplayUp
		Set-PSReadlineKeyHandler -Key "Ctrl+Alt+n"       -Function ScrollDisplayDown
	}
}

Export-ModuleMember -Function Install-KeyHandlers