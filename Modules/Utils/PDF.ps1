function PDFdump {
	$FILES = Get-FileNames -Recursive ".pdf$|.PDF$"
	foreach($File in $Files) {
		CreateDirectory "out/dump"
		pdftk $File dump_data output (Join-Path "out/dump" "${File}.txt")
	}
}

function PDFupdate {
	$FILES = Get-FileNames -Recursive ".pdf$|.PDF$"
	foreach($File in $Files) {
		if (Test-Path (Join-Path "out/dump" "${File}.txt")) {
			pdftk $File update_info (Join-Path "out/dump" "${File}.txt") output (Join-Path "out" "${File}")
		}
	}
}