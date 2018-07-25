function prompt {
	$TEMP  = $(Get-Date -UFormat "%H:%M")
	$TEMP += " "

	if ($Projects)
	{
		$PATTERN = $Projects + "*"
		if ( $(Get-Location).path -like $PATTERN )
		{
			$PROJ += $($(Get-Location).path.split($Projects)[1].split('/')[1])
			if ($PROJ)
			{
				$TEMP += $($(Get-Location).path.split($Projects + "/")[1]).Split("/")[0]
				if ($($(Get-Location).path.split($Projects + "/")[1]).Split("/")[1])
				{
					$TEMP += "("
					$TEMP += $($(Get-Location).path.split($Projects + "/")[1] | Split-Path -Leaf)
					$TEMP += ")"
				}
				else
				{
					$TEMP += "(.)"
				}
				# $TEMP += $($(Get-Location).path.split($Projects + "/")[1]).replace('/','>')
			}
			else {
				$TEMP += "("
				$TEMP += $(Get-Location | Split-Path -Leaf)
				$TEMP += ")"
			}
		}
		else {
			$TEMP += "("
			$TEMP += $(Get-Location | Split-Path -Leaf)
			$TEMP += ")"
		}
	}
	else {
		$TEMP += "("
		$TEMP += $(Get-Location | Split-Path -Leaf)
		$TEMP += ")"
	}
	$TEMP += "> "

	return $TEMP
}
function installTool {

}

function setup {
	$Global:Workspace = "$Home/Workspace"
	$Global:Projects = "$Workspace/Projects"
	$Global:Tools = "$Workspace/Tools"
	$Global:Scripts = "$Tools/Scripts"

	$MYPATH = $Global:Scripts + ":"

	## PATHS
	$GOPATH = "$Tools/go/bin"
	$GITPATH = "$Tools/git/bin"
	$VSCODEPATH = "$Tools/VSCode/bin"
	$PYTHONPATH = "$Tools/python"
	$KOTLINPATH = "$Tools/kotlinc"

	$MYPATH += $GOPATH + ":"
	$MYPATH += $GITPATH + ":"
	$MYPATH += $VSCODEPATH + ":"
	$MYPATH += $PYTHONPATH + ":"
	$MYPATH += $KOTLINPATH + ":"
	$MYPATH += $env:PATH

	$env:PATH = $MYPATH
}

setup
cd $Workspace

# Host Foreground
$Host.PrivateData.ErrorForegroundColor = 'Red'
$Host.PrivateData.WarningForegroundColor = 'Yellow'
$Host.PrivateData.DebugForegroundColor = 'Green'
$Host.PrivateData.VerboseForegroundColor = 'Blue'
$Host.PrivateData.ProgressForegroundColor = 'Gray'

# Host Background
$Host.PrivateData.ErrorBackgroundColor = 'Gray'
$Host.PrivateData.WarningBackgroundColor = 'Gray'
$Host.PrivateData.DebugBackgroundColor = 'Gray'
$Host.PrivateData.VerboseBackgroundColor = 'Gray'
$Host.PrivateData.ProgressBackgroundColor = 'Cyan'

# Check for PSReadline
if (Get-Module -ListAvailable -Name "PSReadline") {
    $options = Get-PSReadlineOption

    # Foreground
    $options.CommandForegroundColor = 'Yellow'
    $options.ContinuationPromptForegroundColor = 'DarkYellow'
    $options.DefaultTokenForegroundColor = 'DarkYellow'
    $options.EmphasisForegroundColor = 'Cyan'
    $options.ErrorForegroundColor = 'Red'
    $options.KeywordForegroundColor = 'Green'
    $options.MemberForegroundColor = 'DarkGreen'
    $options.NumberForegroundColor = 'DarkGreen'
    $options.OperatorForegroundColor = 'DarkCyan'
    $options.ParameterForegroundColor = 'DarkCyan'
    $options.StringForegroundColor = 'Blue'
    $options.TypeForegroundColor = 'DarkBlue'
    $options.VariableForegroundColor = 'Green'

    # Background
    $options.CommandBackgroundColor = 'White'
    $options.ContinuationPromptBackgroundColor = 'White'
    $options.DefaultTokenBackgroundColor = 'White'
    $options.EmphasisBackgroundColor = 'White'
    $options.ErrorBackgroundColor = 'White'
    $options.KeywordBackgroundColor = 'White'
    $options.MemberBackgroundColor = 'White'
    $options.NumberBackgroundColor = 'White'
    $options.OperatorBackgroundColor = 'White'
    $options.ParameterBackgroundColor = 'White'
    $options.StringBackgroundColor = 'White'
    $options.TypeBackgroundColor = 'White'
    $options.VariableBackgroundColor = 'White'
}

# https://dl.google.com/go/go1.10.3.linux-386.tar.gz

# https://github.com/JetBrains/kotlin/releases/download/v1.2.51/kotlin-compiler-1.2.51.zip
# https://dl.google.com/go/go1.10.3.windows-amd64.zip
# https://www.python.org/ftp/python/3.7.0/python-3.7.0-embed-amd64.zip