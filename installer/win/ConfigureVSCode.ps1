param(
    [Parameter()]
    [string]$BinPath
)
$UserSetting = "$env:APPDATA\Code\User\settings.Json"
$Json = Get-Content $UserSetting -raw | ConvertFrom-Json 
if($null -eq $Json) {
    $Json = Write-Output "{}" | ConvertFrom-Json
}
try {
    $Json.'Preda.path' = $BinPath
} catch {
    $Json | Add-Member -MemberType NoteProperty -Name "Preda.path" -Value $BinPath
}
$Json | ConvertTo-Json -depth 32 | Out-File -Encoding ASCII $UserSetting