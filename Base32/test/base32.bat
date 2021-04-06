@echo off
pushd %~dp0

set exe="%~dp0base32.exe"
set log="%~dp0base32.log"

echo Start Time: %TIME% >> %log%
for /F "tokens=*" %%A in (base32.txt) do (
	%exe% %%A >> %log%
)
echo Ending Time: %TIME% >> %log%

popd
exit