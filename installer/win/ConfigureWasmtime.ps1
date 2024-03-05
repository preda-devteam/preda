param(
    [string]$wasmString,
    [string]$AppPath
)
if ($wasmString -eq "true" -or $wasmString -eq "false") {
    $wasm = [bool]::Parse($wasmString)

    $configFilePath = Join-Path -Path $AppPath -ChildPath "config.json"

    if (Test-Path $configFilePath) {
        try {
            $configContent = Get-Content -Path $configFilePath -Raw | ConvertFrom-Json
            $configContent.wasm = $Wasm
            $configContent | ConvertTo-Json -Depth 10 | Set-Content -Path $configFilePath -Encoding UTF8 -Force
            Write-Host "config.json create and update successed: $configFilePath"
        }
        catch {
            Write-Host "config.json create and update failed: $_"
        }
    }
    else {
        $configContent = @{
            "wasm" = $Wasm
        } | ConvertTo-Json -Depth 10

        try {
            $configContent | Set-Content -Path $configFilePath -Encoding UTF8 -Force
            Write-Host "config.json update successed: $configFilePath"
        }
        catch {
            Write-Host "config.json update successed: $_"
        }
    }
}
else {
    Write-Host "wasmString value error, pls inport "true" or "false"."
}