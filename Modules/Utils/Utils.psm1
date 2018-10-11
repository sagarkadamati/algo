Function Get-MP3MetaData {
	[CmdletBinding()]
	[Alias()]
	[OutputType([Psobject])]
	Param
	(
		[String] [Parameter(Mandatory = $true, ValueFromPipeline = $true)] $Directory
	)

	Begin {
		$shell = New-Object -ComObject "Shell.Application"
	}
	Process {

		Foreach ($Dir in $Directory) {
			$ObjDir = $shell.NameSpace($Dir)
			$Files = Get-ChildItem $Dir | ? {$_.Extension -in '.mp3', '.mp4'}

			Foreach ($File in $Files) {
				$ObjFile = $ObjDir.parsename($File.Name)
				$MetaData = @{}
				$MP3 = ($ObjDir.Items() | Where-Object {$_.path -like "*.mp3" -or $_.path -like "*.mp4"})
				$PropertArray = 0, 1, 2, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 27, 28, 36, 220, 223

				Foreach ($item in $PropertArray) {
					If ($ObjDir.GetDetailsOf($ObjFile, $item)) { #To avoid empty values
						$MetaData[$($ObjDir.GetDetailsOf($MP3, $item))] = $ObjDir.GetDetailsOf($ObjFile, $item)
					}

				}

				New-Object psobject -Property $MetaData | select *, @{n = "Directory"; e = {$Dir}}, @{n = "Fullname"; e = {Join-Path $Dir $File.Name -Resolve}}, @{n = "Extension"; e = {$File.Extension}}
			}
		}
	}
	End {
	}
}

function Gen-Patch {
	param(
		[String]$Patch
	)
	Process {
		git format-patch HEAD~ --stdout > $($Patch + ".patch")
	}
}

function Apply-Patch {
	param(
		[String]$Patch
	)
	Process {
		git apply --stat $($Patch + ".patch")
	}
}

function Get-Repos {
	New-Item -Type Directory SimpleMobileTools
	git clone https://github.com/SimpleMobileTools/Simple-Gallery
	git clone https://github.com/SimpleMobileTools/Simple-Calendar
	git clone https://github.com/SimpleMobileTools/Simple-Contacts
	git clone https://github.com/SimpleMobileTools/Simple-Commons
	git clone https://github.com/SimpleMobileTools/Simple-Notes
	git clone https://github.com/SimpleMobileTools/Simple-App-Launcher
	git clone https://github.com/SimpleMobileTools/Simple-Draw
	git clone https://github.com/SimpleMobileTools/Simple-Camera
	git clone https://github.com/SimpleMobileTools/Simple-File-Manager
	git clone https://github.com/SimpleMobileTools/Simple-Thank-You
	git clone https://github.com/SimpleMobileTools/Simple-Calculator
	git clone https://github.com/SimpleMobileTools/Simple-Clock
	git clone https://github.com/SimpleMobileTools/Simple-Music-Player
	git clone https://github.com/SimpleMobileTools/Simple-Flashlight
	git clone https://github.com/SimpleMobileTools/General-Discussion
	git clone https://github.com/SimpleMobileTools/simplemobiletools.github.io
}

function Get-PadZeros($NOS, $Count) {

}

function ReverseFileNos {
	$NOS = 0
	$Files = Get-ChildItem -File
	[array]::Reverse($Files)

	$Count     = 0
	$Digits    = 1

	$TCount    = $Files.Count
	while($TCount -ne 0) {
		$TCount = [Math]::Abs($TCount / 10)
		$Digits++

		if ($TCount -ge 10) { continue } else { break }
	}

	foreach ($File in $Files) {
		$Title = ($File -split $([regex]::Match($File.BaseName, '(^[0-9]*[ ]*)').Groups[0].Value))[1]
		$NOS++

		$NewTitle = ([String]$NOS) | % PadLeft $Digits '0'
		$NewTitle += " $Title"

		Move-Item -Force $File $NewTitle
	}
}

Export-ModuleMember -Function Get-MP3MetaData, Get-Repos, Update-Files, ReverseFileNos