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

function Get-Mp4FromTS {
	## https://superuser.com/questions/692990/use-ffmpeg-copy-codec-to-combine-ts-files-into-a-single-mp4

	## Under windows:
	# copy /b segment1_0_av.ts+segment2_0_av.ts+segment3_0_av.ts all.ts
	# ffmpeg -i all.ts -acodec copy -vcodec copy all.mp4

	## Under GNU/Linux, using bash:
	# cat segment1_0_av.ts segment2_0_av.ts segment3_0_av.ts > all.ts
	# ffmpeg -i all.ts -acodec copy -vcodec copy all.mp4

	# $DLoc = Join-Path $WorkspaceLocation "Host Star\in.startv.hotstar\files\downloads"
	# $Folders = Get-ChildItem -Directory -LiteralPath $DLoc

	# $Folders = Get-ChildItem -Directory
	# foreach ($Folder in $Folders) {
	# 	Set-Location $(Join-Path $DLoc $Folder)
	# 	$ChunkCount = (Get-ChildItem -Directory).Count

	# 	$Count = 0

	# 	$AllChunks = ""
	# 	Remove-Item -ErrorAction Ignore -Force list.txt
	# 	while ($Count -lt $ChunkCount) {
	# 		$Chunk = Join-Path "ts$Count" "chunk.ts"
	# 		$Count++

	# 		$Chunk
	# 		"file '$Chunk'" >> list.txt

	# 	# 	$AllChunks += $Chunk

	# 	# 	if ($Count -lt $ChunkCount) {
	# 	# 		$AllChunks += "+"
	# 	# 	}
	# 	}
	# 	# $AllChunks
	# 	# cmd /c copy.exe $AllChunks all.ts
	# 	ffmpeg -f concat -i list.txt -c copy all.ts
	# 	ffmpeg -i all.ts -acodec copy -vcodec copy all.mp4
	# }
	# ffmpeg  -allowed_extensions ALL -i *local*.m3u8 -c copy video.mp4

	$Folders = Get-ChildItem -Directory
	foreach ($Folder in $Folders) {
		$CurrentLoc = Get-Location
		Set-Location "$Folder"

		if (!(Test-Path "video.mp4")) {
			$LocalM3U8  = Get-ChildItem -File -Filter "*local*.m3u8"
			$RemoteM3U8 = Get-ChildItem -File -Filter "*sub*.m3u8"

			if (!(Test-Path "crypt.key")) {
				$CryptFile = ((Get-Content $RemoteM3U8 | Select-String URI).Line -split 'URI="')[1] -replace """$"

				Write-Host Downloading... $CryptFile
				Invoke-WebRequest -Uri $CryptFile -OutFile crypt.key
			}

			((Get-Content $LocalM3U8) -replace "http://localhost:\d+/storage/emulated/0/Android/data/in.startv.hotstar/files/downloads/\d+/","") -replace "http://localhost:\d+/data/user/0/in.startv.hotstar/app_downloads/\d+/ts0/","" | Set-Content data.m3u8

			ffmpeg  -allowed_extensions ALL -i data.m3u8 -c copy video.mp4
		}

		Set-Location $CurrentLoc
	}
}

function Sync-HSKeys {
	$SLoc = "${$WorkspaceLocation}\Host Star\downloads"
	$MLoc = "This PC\Galaxy A6+\Phone\Android\data\in.startv.hotstar\files\downloads"


	$Folders = Get-ChildItem -Directory
	foreach ($Folder in $Folders) {
		$CurrentLoc = Get-Location
		Set-Location "$Folder"

		if (!(Test-Path "video.mp4")) {
			$LocalM3U8  = Get-ChildItem -File -Filter "*local*.m3u8"
			$RemoteM3U8 = Get-ChildItem -File -Filter "*sub*.m3u8"

			if (!(Test-Path "crypt.key")) {
				$CryptFile = ((Get-Content $RemoteM3U8 | Select-String URI).Line -split 'URI="')[1] -replace """$"

				Write-Host Downloading... $CryptFile
				Invoke-WebRequest -Uri $CryptFile -OutFile crypt.key
			}

			((Get-Content $LocalM3U8) -replace "http://localhost:\d+/storage/emulated/0/Android/data/in.startv.hotstar/files/downloads/\d+/","") -replace "http://localhost:\d+/data/user/0/in.startv.hotstar/app_downloads/\d+/ts0/","" | Set-Content data.m3u8

			ffmpeg  -allowed_extensions ALL -i data.m3u8 -c copy video.mp4
		}

		Set-Location $CurrentLoc
	}
}

Export-ModuleMember -Function Get-MP3MetaData, Get-Repos, Update-Files, ReverseFileNos, Get-Mp4FromTS