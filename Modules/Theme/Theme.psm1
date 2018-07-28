function LTheme($Time) {
	if ([System.Environment]::OSVersion.Platform -eq "Win32NT") {
		$lnk = & $(Join-Path $PSScriptRoot "GetLink.ps1") "$Home\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Windows PowerShell\Windows PowerShell.lnk"

		# Set Common Solarized Colors
		$lnk.ConsoleColors[0]  = "#002b36"
		$lnk.ConsoleColors[8]  = "#073642"
		$lnk.ConsoleColors[2]  = "#586e75"
		$lnk.ConsoleColors[6]  = "#657b83"
		$lnk.ConsoleColors[1]  = "#839496"
		$lnk.ConsoleColors[3]  = "#93a1a1"
		$lnk.ConsoleColors[7]  = "#eee8d5"
		$lnk.ConsoleColors[15] = "#fdf6e3"
		$lnk.ConsoleColors[14] = "#b58900"
		$lnk.ConsoleColors[4]  = "#cb4b16"
		$lnk.ConsoleColors[12] = "#dc322f"
		$lnk.ConsoleColors[13] = "#d33682"
		$lnk.ConsoleColors[5]  = "#6c71c4"
		$lnk.ConsoleColors[9]  = "#268bd2"
		$lnk.ConsoleColors[11] = "#2aa198"
		$lnk.ConsoleColors[10] = "#859900"

		# Set Light/Dark Theme-Specific Colors
		if ($Time -match "Night") {
			$lnk.PopUpBackgroundColor  = 0xf
			$lnk.PopUpTextColor        = 0x6
			$lnk.ScreenBackgroundColor = 0x0
			$lnk.ScreenTextColor       = 0x1
		}
		else {
			$lnk.PopUpBackgroundColor  = 0x0
			$lnk.PopUpTextColor        = 0x1
			$lnk.ScreenBackgroundColor = 0xf
			$lnk.ScreenTextColor       = 0x6
		}
		$lnk.Save()
	}
}

function STheme($Time) {
	if ($Time -match "Night") {

		# Host UI
		$Host.UI.RawUI.BackgroundColor                 = 'Black'
		$Host.UI.RawUI.ForegroundColor                 = 'Cyan'

		# Host Foreground
		$Host.PrivateData.ErrorForegroundColor         = 'Red'
		$Host.PrivateData.WarningForegroundColor       = 'Yellow'
		$Host.PrivateData.DebugForegroundColor         = 'Green'
		$Host.PrivateData.VerboseForegroundColor       = 'Blue'
		$Host.PrivateData.ProgressForegroundColor      = 'Gray'

		# Host Background
		$Host.PrivateData.ErrorBackgroundColor         = 'DarkGray'
		$Host.PrivateData.WarningBackgroundColor       = 'DarkGray'
		$Host.PrivateData.DebugBackgroundColor         = 'DarkGray'
		$Host.PrivateData.VerboseBackgroundColor       = 'DarkGray'
		$Host.PrivateData.ProgressBackgroundColor      = 'Cyan'

		# Check for PSReadline
		if (Get-Module -ListAvailable -Name "PSReadline") {
			$options = Get-PSReadlineOption

			# Foreground
			$options.CommandForegroundColor            = 'Yellow'
			$options.ContinuationPromptForegroundColor = 'DarkBlue'
			$options.DefaultTokenForegroundColor       = 'DarkBlue'
			$options.EmphasisForegroundColor           = 'Cyan'
			$options.ErrorForegroundColor              = 'Red'
			$options.KeywordForegroundColor            = 'Green'
			$options.MemberForegroundColor             = 'DarkCyan'
			$options.NumberForegroundColor             = 'DarkCyan'
			$options.OperatorForegroundColor           = 'DarkGreen'
			$options.ParameterForegroundColor          = 'DarkGreen'
			$options.StringForegroundColor             = 'Blue'
			$options.TypeForegroundColor               = 'DarkYellow'
			$options.VariableForegroundColor           = 'Green'

			# Background
			$options.CommandBackgroundColor            = 'Black'
			$options.ContinuationPromptBackgroundColor = 'Black'
			$options.DefaultTokenBackgroundColor       = 'Black'
			$options.EmphasisBackgroundColor           = 'Black'
			$options.ErrorBackgroundColor              = 'Black'
			$options.KeywordBackgroundColor            = 'Black'
			$options.MemberBackgroundColor             = 'Black'
			$options.NumberBackgroundColor             = 'Black'
			$options.OperatorBackgroundColor           = 'Black'
			$options.ParameterBackgroundColor          = 'Black'
			$options.StringBackgroundColor             = 'Black'
			$options.TypeBackgroundColor               = 'Black'
			$options.VariableBackgroundColor           = 'Black'
		}
	}
	else {
		# Host UI
		$Host.UI.RawUI.BackgroundColor                 = 'White'
		$Host.UI.RawUI.ForegroundColor                 = 'Cyan'

		# Host Foreground
		$Host.PrivateData.ErrorForegroundColor         = 'Red'
		$Host.PrivateData.WarningForegroundColor       = 'Yellow'
		$Host.PrivateData.DebugForegroundColor         = 'Green'
		$Host.PrivateData.VerboseForegroundColor       = 'Blue'
		$Host.PrivateData.ProgressForegroundColor      = 'Gray'

		# Host Background
		$Host.PrivateData.ErrorBackgroundColor         = 'Gray'
		$Host.PrivateData.WarningBackgroundColor       = 'Gray'
		$Host.PrivateData.DebugBackgroundColor         = 'Gray'
		$Host.PrivateData.VerboseBackgroundColor       = 'Gray'
		$Host.PrivateData.ProgressBackgroundColor      = 'Cyan'

		# Check for PSReadline
		if (Get-Module -ListAvailable -Name "PSReadline") {
			$options = Get-PSReadlineOption

			# Foreground
			$options.CommandForegroundColor            = 'Yellow'
			$options.ContinuationPromptForegroundColor = 'DarkYellow'
			$options.DefaultTokenForegroundColor       = 'DarkYellow'
			$options.EmphasisForegroundColor           = 'Cyan'
			$options.ErrorForegroundColor              = 'Red'
			$options.KeywordForegroundColor            = 'Green'
			$options.MemberForegroundColor             = 'DarkGreen'
			$options.NumberForegroundColor             = 'DarkGreen'
			$options.OperatorForegroundColor           = 'DarkCyan'
			$options.ParameterForegroundColor          = 'DarkCyan'
			$options.StringForegroundColor             = 'Blue'
			$options.TypeForegroundColor               = 'DarkBlue'
			$options.VariableForegroundColor           = 'Green'

			# Background
			$options.CommandBackgroundColor            = 'White'
			$options.ContinuationPromptBackgroundColor = 'White'
			$options.DefaultTokenBackgroundColor       = 'White'
			$options.EmphasisBackgroundColor           = 'White'
			$options.ErrorBackgroundColor              = 'White'
			$options.KeywordBackgroundColor            = 'White'
			$options.MemberBackgroundColor             = 'White'
			$options.NumberBackgroundColor             = 'White'
			$options.OperatorBackgroundColor           = 'White'
			$options.ParameterBackgroundColor          = 'White'
			$options.StringBackgroundColor             = 'White'
			$options.TypeBackgroundColor               = 'White'
			$options.VariableBackgroundColor           = 'White'
		}
	}
}

function NightTheme {
	STheme "Night"
	LTheme "Night"
	Clear-Host
}

function DayTheme {
	STheme "Day"
	LTheme "Day"
	Clear-Host
}

function Update-Theme {
	if ($Host.UI.RawUI.BackgroundColor -match "White")
	{
		STheme "Day"
	}
	else
	{
		STheme "Night"
	}
}

Export-ModuleMember -Function Update-Theme, NightTheme, DayTheme