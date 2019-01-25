# $ColorBlack		= "#002b36" # base03
# $ColorDarkBlue	= "#073642" # base02
# $ColorDarkGreen	= "#586e75" # base01
# $ColorDarkCyan	= "#657b83" # base00
# $ColorDarkRed		= "#839496" # base0
# $ColorDarkMagenta	= "#93a1a1" # base1
# $ColorDarkYellow	= "#eee8d5" # base2
# $ColorGray		= "#fdf6e3" # base3
# $ColorDarkGray	= "#b58900" # yellow
# $ColorBlue		= "#cb4b16" # orange
# $ColorGreen		= "#dc322f" # red
# $ColorCyan		= "#d33682" # magenta
# $ColorRed			= "#6c71c4" # violet
# $ColorMagenta		= "#268bd2" # blue
# $ColorYellow		= "#2aa198" # cyan
# $ColorWhite		= "#859900" # green

function LTheme($Time) {

	# Palette
	$ColorBlack			= "#073642" # base02
	$ColorDarkBlue		= "#dc322f" # red
	$ColorDarkGreen		= "#859900" # green
	$ColorDarkCyan		= "#b58900" # yellow
	$ColorDarkRed		= "#268bd2" # blue
	$ColorDarkMagenta	= "#d33682" # magenta
	$ColorDarkYellow	= "#2aa198" # cyan
	$ColorGray			= "#eee8d5" # base2
	$ColorDarkGray		= "#002b36" # base03
	$ColorBlue			= "#cb4b16" # orange
	$ColorGreen			= "#586e75" # base01
	$ColorCyan			= "#657b83" # base00
	$ColorRed			= "#839496" # base0
	$ColorMagenta		= "#6c71c4" # violet
	$ColorYellow		= "#93a1a1" # base1
	$ColorWhite			= "#fdf6e3" # base3

	if ([System.Environment]::OSVersion.Platform -eq "Win32NT") {
		## Set Common Colors In The Link
		$lnk = & "${PSScriptRoot}\GetLink.ps1" "${Home}\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Windows PowerShell\Windows PowerShell.lnk"

		# Set Palette
		$lnk.ConsoleColors[0]  = $ColorBlack		# base02
		$lnk.ConsoleColors[1]  = $ColorDarkBlue		# red
		$lnk.ConsoleColors[2]  = $ColorDarkGreen	# green
		$lnk.ConsoleColors[3]  = $ColorDarkCyan		# yellow
		$lnk.ConsoleColors[4]  = $ColorDarkRed		# blue
		$lnk.ConsoleColors[5]  = $ColorDarkMagenta	# magenta
		$lnk.ConsoleColors[6]  = $ColorDarkYellow	# cyan
		$lnk.ConsoleColors[7]  = $ColorGray			# base2
		$lnk.ConsoleColors[8]  = $ColorDarkGray		# base03
		$lnk.ConsoleColors[9]  = $ColorBlue			# orange
		$lnk.ConsoleColors[10] = $ColorGreen		# base01
		$lnk.ConsoleColors[11] = $ColorCyan			# base00
		$lnk.ConsoleColors[12] = $ColorRed			# base0
		$lnk.ConsoleColors[13] = $ColorMagenta		# violet
		$lnk.ConsoleColors[14] = $ColorYellow		# base1
		$lnk.ConsoleColors[15] = $ColorWhite		# base3

		# Set Light/Dark Theme-Specific Colors
		if ($Time -match "Night") {
			$lnk.PopUpBackgroundColor  = 0x0 # index in palette
			$lnk.ScreenBackgroundColor = 0x8
			$lnk.PopUpTextColor        = 0xC
			$lnk.ScreenTextColor       = 0xE
		}
		else {
			$lnk.PopUpBackgroundColor  = 0x7
			$lnk.ScreenBackgroundColor = 0xF
			$lnk.PopUpTextColor        = 0xB
			$lnk.ScreenTextColor       = 0xA
		}
		$lnk.Save()
	}
}

function STheme($Time) {
	# [Enum]::GetValues([System.ConsoleColor])

	if ($Time -match "Night") {
		$ScreenBackgroundColor		= [ConsoleColor]::DarkGray
		$ScreenTextColor			= [ConsoleColor]::Yellow
		$PopUpBackgroundColor		= [ConsoleColor]::Black
		$PopUpTextColor				= [ConsoleColor]::Red
	}
	else {
		$ScreenBackgroundColor		= [ConsoleColor]::White
		$ScreenTextColor			= [ConsoleColor]::Green
		$PopUpBackgroundColor		= [ConsoleColor]::Gray
		$PopUpTextColor				= [ConsoleColor]::Cyan
	}

	# Host UI
	$Host.UI.RawUI.BackgroundColor                 = $ScreenBackgroundColor
	$Host.UI.RawUI.ForegroundColor                 = $ScreenTextColor

	# Host Background
	$Host.PrivateData.ErrorBackgroundColor         = $ScreenBackgroundColor
	$Host.PrivateData.WarningBackgroundColor       = $ScreenBackgroundColor
	$Host.PrivateData.DebugBackgroundColor         = $ScreenBackgroundColor
	$Host.PrivateData.VerboseBackgroundColor       = $ScreenBackgroundColor
	$Host.PrivateData.ProgressBackgroundColor      = $PopUpBackgroundColor

	# Host Foreground
	$Host.PrivateData.ErrorForegroundColor         = [ConsoleColor]::DarkBlue  # RED
	$Host.PrivateData.WarningForegroundColor       = [ConsoleColor]::DarkGreen # GREEN
	$Host.PrivateData.DebugForegroundColor         = [ConsoleColor]::Red
	$Host.PrivateData.VerboseForegroundColor       = [ConsoleColor]::Blue
	$Host.PrivateData.ProgressForegroundColor      = $PopUpTextColor

	# Check for PSReadline
	if (Get-Module -ListAvailable -Name "PSReadline") {
		try {
			$PSReadLineOptions = @{
				BellStyle = "None"
				Colors = @{
					# Background
					"CommandBackground"            = $ScreenBackgroundColor
					"ContinuationPromptBackground" = $ScreenBackgroundColor
					"DefaultTokenBackground"       = $ScreenBackgroundColor
					"EmphasisBackground"           = $ScreenBackgroundColor
					"ErrorBackground"              = $ScreenBackgroundColor
					"KeywordBackground"            = $ScreenBackgroundColor
					"MemberBackground"             = $ScreenBackgroundColor
					"NumberBackground"             = $ScreenBackgroundColor
					"OperatorBackground"           = $ScreenBackgroundColor
					"ParameterBackground"          = $ScreenBackgroundColor
					"StringBackground"             = $ScreenBackgroundColor
					"TypeBackground"               = $ScreenBackgroundColor
					"VariableBackground"           = $ScreenBackgroundColor

					# Foreground
					"Command"                      = [ConsoleColor]::Yellow
					"ContinuationPrompt"           = [ConsoleColor]::DarkYellow
					"DefaultToken"                 = [ConsoleColor]::DarkYellow
					"Emphasis"                     = [ConsoleColor]::Cyan
					"Error"                        = [ConsoleColor]::Red
					"Keyword"                      = [ConsoleColor]::Green
					"Member"                       = [ConsoleColor]::DarkGreen
					"Number"                       = [ConsoleColor]::DarkGreen
					"Operator"                     = [ConsoleColor]::DarkCyan
					"Parameter"                    = [ConsoleColor]::DarkCyan
					"String"                       = [ConsoleColor]::Blue
					"Type"                         = [ConsoleColor]::DarkBlue
					"Variable"                     = [ConsoleColor]::Green
				}
			}
			Set-PSReadLineOption @PSReadLineOptions
		} catch {
			$options = Get-PSReadlineOption

			$options.BellStyle = "None"

			# Background
			$options.CommandBackgroundColor            = $ScreenBackgroundColor
			$options.ContinuationPromptBackgroundColor = $ScreenBackgroundColor
			$options.DefaultTokenBackgroundColor       = $ScreenBackgroundColor
			$options.EmphasisBackgroundColor           = $ScreenBackgroundColor
			$options.ErrorBackgroundColor              = $ScreenBackgroundColor
			$options.KeywordBackgroundColor            = $ScreenBackgroundColor
			$options.MemberBackgroundColor             = $ScreenBackgroundColor
			$options.NumberBackgroundColor             = $ScreenBackgroundColor
			$options.OperatorBackgroundColor           = $ScreenBackgroundColor
			$options.ParameterBackgroundColor          = $ScreenBackgroundColor
			$options.StringBackgroundColor             = $ScreenBackgroundColor
			$options.TypeBackgroundColor               = $ScreenBackgroundColor
			$options.VariableBackgroundColor           = $ScreenBackgroundColor

			# Foreground
			$options.CommandForegroundColor            = [ConsoleColor]::Yellow
			$options.ContinuationPromptForegroundColor = [ConsoleColor]::DarkYellow
			$options.DefaultTokenForegroundColor       = [ConsoleColor]::DarkYellow
			$options.EmphasisForegroundColor           = [ConsoleColor]::Cyan
			$options.ErrorForegroundColor              = [ConsoleColor]::Red
			$options.KeywordForegroundColor            = [ConsoleColor]::Green
			$options.MemberForegroundColor             = [ConsoleColor]::DarkGreen
			$options.NumberForegroundColor             = [ConsoleColor]::DarkGreen
			$options.OperatorForegroundColor           = [ConsoleColor]::DarkCyan
			$options.ParameterForegroundColor          = [ConsoleColor]::DarkCyan
			$options.StringForegroundColor             = [ConsoleColor]::Blue
			$options.TypeForegroundColor               = [ConsoleColor]::DarkBlue
			$options.VariableForegroundColor           = [ConsoleColor]::Green
		}
	}
}

function NightTheme {
	LTheme "Night"
	STheme "Night"
	Clear-Host
}

function DayTheme {
	LTheme "Day"
	STheme "Day"
	Clear-Host
}

function Update-Theme {
	if ([System.Environment]::OSVersion.Platform -eq "Win32NT") {
		if (($Host.UI.RawUI.BackgroundColor -match [ConsoleColor]::White)) {
			STheme "Day"
		} else {
			STheme "Night"
		}
	} else {
		STheme "Day"
	}
}

Export-ModuleMember -Function Update-Theme, NightTheme, DayTheme