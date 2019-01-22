# # [ConsoleColor]::Black -> base03: #002b36;
# $lnk.ConsoleColors[0]  = "#002b36"

# # [ConsoleColor]::DarkBlue -> base02: #073642;
# $lnk.ConsoleColors[1]  = "#839496"

# # [ConsoleColor]::DarkGreen -> base01: #586e75;
# $lnk.ConsoleColors[2]  = "#586e75"

# # [ConsoleColor]::DarkCyan -> base00: #657b83;
# $lnk.ConsoleColors[3]  = "#93a1a1"

# # [ConsoleColor]::DarkRed -> base0: #839496;
# $lnk.ConsoleColors[4]  = "#cb4b16"

# # [ConsoleColor]::DarkMagenta -> base1: #93a1a1;
# $lnk.ConsoleColors[5]  = "#6c71c4"

# # [ConsoleColor]::DarkYellow -> base2: #eee8d5;
# $lnk.ConsoleColors[6]  = "#657b83"

# # [ConsoleColor]::Gray -> base3: #fdf6e3;
# $lnk.ConsoleColors[7]  = "#eee8d5"

# # [ConsoleColor]::DarkGray -> yellow: #b58900;
# $lnk.ConsoleColors[8]  = "#073642"

# # [ConsoleColor]::Blue -> orange: #cb4b16;
# $lnk.ConsoleColors[9]  = "#268bd2"

# # [ConsoleColor]::Green -> red: #dc322f;
# $lnk.ConsoleColors[10] = "#859900"

# # [ConsoleColor]::Cyan -> magenta: #d33682;
# $lnk.ConsoleColors[11] = "#2aa198"

# # [ConsoleColor]::Red -> violet: #6c71c4;
# $lnk.ConsoleColors[12] = "#dc322f"

# # [ConsoleColor]::Magenta -> blue: #268bd2;
# $lnk.ConsoleColors[13] = "#d33682"

# # [ConsoleColor]::Yellow -> cyan: #2aa198;
# $lnk.ConsoleColors[14] = "#b58900"

# # [ConsoleColor]::White -> green: #859900;
# $lnk.ConsoleColors[15] = "#fdf6e3"

function LTheme($Time) {
	if ([System.Environment]::OSVersion.Platform -eq "Win32NT") {
		## Set Common Colors In The Link
		$lnk = & "${PSScriptRoot}\GetLink.ps1" "${Home}\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Windows PowerShell\Windows PowerShell.lnk"

		# [ConsoleColor]::Black -> base03: #002b36;
		$lnk.ConsoleColors[0]  = "#002b36"

		# [ConsoleColor]::DarkBlue -> base02: #073642;
		$lnk.ConsoleColors[1]  = "#073642"

		# [ConsoleColor]::DarkGreen -> base01: #586e75;
		$lnk.ConsoleColors[2]  = "#586e75"

		# [ConsoleColor]::DarkCyan -> base00: #657b83;
		$lnk.ConsoleColors[3]  = "#657b83"

		# [ConsoleColor]::DarkRed -> base0: #839496;
		$lnk.ConsoleColors[4]  = "#839496"

		# [ConsoleColor]::DarkMagenta -> base1: #93a1a1;
		$lnk.ConsoleColors[5]  = "#93a1a1"

		# [ConsoleColor]::DarkYellow -> base2: #eee8d5;
		$lnk.ConsoleColors[6]  = "#eee8d5"

		# [ConsoleColor]::Gray -> base3: #fdf6e3;
		$lnk.ConsoleColors[7]  = "#fdf6e3"

		# [ConsoleColor]::DarkGray -> yellow: #b58900;
		$lnk.ConsoleColors[8]  = "#b58900"

		# [ConsoleColor]::Blue -> orange: #cb4b16;
		$lnk.ConsoleColors[9]  = "#cb4b16"

		# [ConsoleColor]::Green -> red: #dc322f;
		$lnk.ConsoleColors[10] = "#dc322f"

		# [ConsoleColor]::Cyan -> magenta: #d33682;
		$lnk.ConsoleColors[11] = "#d33682"

		# [ConsoleColor]::Red -> violet: #6c71c4;
		$lnk.ConsoleColors[12] = "#6c71c4"

		# [ConsoleColor]::Magenta -> blue: #268bd2;
		$lnk.ConsoleColors[13] = "#268bd2"

		# [ConsoleColor]::Yellow -> cyan: #2aa198;
		$lnk.ConsoleColors[14] = "#2aa198"

		# [ConsoleColor]::White -> green: #859900;
		$lnk.ConsoleColors[15] = "#859900"

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
	# [Enum]::GetValues([System.ConsoleColor])

	if ($Time -match "Night") {
		# Host UI
		$Host.UI.RawUI.BackgroundColor                 = [ConsoleColor]::Black
		$Host.UI.RawUI.ForegroundColor                 = [ConsoleColor]::Cyan

		# Host Foreground
		$Host.PrivateData.ErrorForegroundColor         = [ConsoleColor]::Red
		$Host.PrivateData.WarningForegroundColor       = [ConsoleColor]::Yellow
		$Host.PrivateData.DebugForegroundColor         = [ConsoleColor]::Green
		$Host.PrivateData.VerboseForegroundColor       = [ConsoleColor]::Blue
		$Host.PrivateData.ProgressForegroundColor      = [ConsoleColor]::Gray

		# Host Background
		$Host.PrivateData.ErrorBackgroundColor         = [ConsoleColor]::DarkGray
		$Host.PrivateData.WarningBackgroundColor       = [ConsoleColor]::DarkGray
		$Host.PrivateData.DebugBackgroundColor         = [ConsoleColor]::DarkGray
		$Host.PrivateData.VerboseBackgroundColor       = [ConsoleColor]::DarkGray
		$Host.PrivateData.ProgressBackgroundColor      = [ConsoleColor]::Cyan

		# Check for PSReadline
		if (Get-Module -ListAvailable -Name "PSReadline") {
			$PSReadLineOptions = @{
				BellStyle = "None"
				Colors = @{
					"Command"            = "#FF00FF"
					"ContinuationPrompt" = "#FF00FF"
					"Operator"           = "#00FF00"
					"Parameter"          = "#00FF00"
					"Error"              = "#FF0000"

					"Selection"          = "#FFFFFF"
					"DefaultToken"       = "#FFFFFF"

					# "Emphasis"           = "#FFFFFF"
					# "Keyword"            = "#FFFFFF"
					# "Member"             = "#FFFFFF"
					# "Number"             = "#FFFFFF"
					# "String"             = "#FFFFFF"
					# "Type"               = "#FFFFFF"
					# "Variable"           = "#FFFFFF"
					# "Comment"            = "#FFFFFF"
				}
			}
			Set-PSReadLineOption @PSReadLineOptions
		}
	}
	else {
		# Host UI
		$Host.UI.RawUI.BackgroundColor                 = [ConsoleColor]::White
		$Host.UI.RawUI.ForegroundColor                 = [ConsoleColor]::DarkGreen

		# Host Foreground
		$Host.PrivateData.ErrorForegroundColor         = [ConsoleColor]::Red
		$Host.PrivateData.WarningForegroundColor       = [ConsoleColor]::Yellow
		$Host.PrivateData.DebugForegroundColor         = [ConsoleColor]::Green
		$Host.PrivateData.VerboseForegroundColor       = [ConsoleColor]::Blue
		$Host.PrivateData.ProgressForegroundColor      = [ConsoleColor]::Gray

		# Host Background
		$Host.PrivateData.ErrorBackgroundColor         = [ConsoleColor]::Gray
		$Host.PrivateData.WarningBackgroundColor       = [ConsoleColor]::Gray
		$Host.PrivateData.DebugBackgroundColor         = [ConsoleColor]::Gray
		$Host.PrivateData.VerboseBackgroundColor       = [ConsoleColor]::Gray
		$Host.PrivateData.ProgressBackgroundColor      = [ConsoleColor]::Cyan

		# Check for PSReadline
		if (Get-Module -ListAvailable -Name "PSReadline") {
			$PSReadLineOptions = @{
				BellStyle = "None"
				Colors = @{
					# "Command"            = "#FF00FF"
					# "ContinuationPrompt" = "#FF00FF"
					# "Operator"           = "#00FF00"
					# "Parameter"          = "#00FF00"
					# "Error"              = "#FF0000"

					# "Selection"          = "#FFFFFF"
					# "DefaultToken"       = "#FFFFFF"

					# "Emphasis"           = "#FFFFFF"
					# "Keyword"            = "#FFFFFF"
					# "Member"             = "#FFFFFF"
					# "Number"             = "#FFFFFF"
					# "String"             = "#FFFFFF"
					# "Type"               = "#FFFFFF"
					# "Variable"           = "#FFFFFF"
					# "Comment"            = "#FFFFFF"

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

					# Background
					"CommandBackground"            = [ConsoleColor]::White
					"ContinuationPromptBackground" = [ConsoleColor]::White
					"DefaultTokenBackground"       = [ConsoleColor]::White
					"EmphasisBackground"           = [ConsoleColor]::White
					"ErrorBackground"              = [ConsoleColor]::White
					"KeywordBackground"            = [ConsoleColor]::White
					"MemberBackground"             = [ConsoleColor]::White
					"NumberBackground"             = [ConsoleColor]::White
					"OperatorBackground"           = [ConsoleColor]::White
					"ParameterBackground"          = [ConsoleColor]::White
					"StringBackground"             = [ConsoleColor]::White
					"TypeBackground"               = [ConsoleColor]::White
					"VariableBackground"           = [ConsoleColor]::White
				}
			}
			Set-PSReadLineOption @PSReadLineOptions
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
		if ($Host.UI.RawUI.BackgroundColor -match "White") {
			STheme "Day"
		} else {
			STheme "Night"
		}
	} else {
		STheme "Day"
	}
}

Export-ModuleMember -Function Update-Theme, NightTheme, DayTheme