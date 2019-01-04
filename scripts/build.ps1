
param([String]$FileName)

if ($FileName -match "Kotlin/Projects/*") {
	Write-Host $FileName
}