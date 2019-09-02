. "$PSScriptRoot\Audio.ps1"
. "$PSScriptRoot\Video.ps1"

function GetBhagavataSkandam($dir, $sk, $end) {
	$cdir = Get-Location
	if (!$(Test-Path $dir)) {
		New-Item -Type Directory $dir
	}
	Set-Location $dir
	if (!$(Test-Path "html")) {
		New-Item -Type Directory "html"
	}

	$count = 1
	foreach($i in 1..$end ) {
		try {
			# echo "http://telugubhagavatam.org/?tebha&Skanda=${sk}&Ghatta=${i}"
			Invoke-WebRequest -Uri "http://telugubhagavatam.org/?tebha&Skanda=${sk}&Ghatta=${i}" -OutFile "tmp${i}.html"
			$html = New-Object -ComObject "HTMLFile"
			$html.IHTMLDocument2_write($(Get-Content "tmp${i}.html" -raw))
			$title = ($html.all.tags("span") | foreach { if ($_.classname -match "ghatta") { $_.outerText} })
			if ($title -notlike "") {
				$html.all.tags("p") | foreach { if ($_.classname -match "meaning") { $_.outerText; echo ""} } | Out-File -Encoding utf8 "${count} ${title}.md"
				Move-Item "tmp${i}.html" "html/${count}.html"
				$count = $count + 1
			} else {
				Remove-Item "tmp${i}.html"
			}
			# Remove-Item "tmp${i}.html"
		} catch {
			write-warning 'Skandam $sk Ghatta $1 skt found'
			break
		}
	}

	Set-Location $cdir
}

function GetBhagavatam {
	GetBhagavataSkandam "ప్రథమ స్కంధము" 1 41
	GetBhagavataSkandam "ద్వితీయ స్కంధము" 2 36
	GetBhagavataSkandam "తృతీయ స్కంధము" 3 57
	GetBhagavataSkandam "చతుర్థ స్కంధము" 4 28
	GetBhagavataSkandam "పంచమ స్కంధము - పూర్వ" 5.1 16
	GetBhagavataSkandam "పంచమ స్కంధము - ఉత్తర" 5.2 8
	GetBhagavataSkandam "షష్ఠ స్కంధము" 6 17
	GetBhagavataSkandam "సప్తమ స్కంధము" 7 17
	GetBhagavataSkandam "అష్టమ స్కంధము" 8 93
	GetBhagavataSkandam "నవమ స్కంధము" 9 54
	GetBhagavataSkandam "దశమ స్కంధము - పూర్వ" 10.1 211
	GetBhagavataSkandam "దశమ స్కంధము - ఉత్తర" 10.2 91
	GetBhagavataSkandam "ఏకాదశ స్కంధము" 11 19
	GetBhagavataSkandam "ద్వాదశ స్కంధము" 12 13
}

Export-ModuleMember -Function ConcatVideos, AutoCropVideos, AnalizeVideos, GenVideos
Export-ModuleMember -Function Get-SriChalapathiRaoAudio, Update-ID3Files, GetBhagavatam