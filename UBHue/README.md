# Installation

Copy the files to your inc/plugins folder and enable it through the AdminCP.

# Usage

You must alter the following templates:
* Ungrouped Templates > headerinclude
* Member Templates > member_profile_groupimage
* Post Bit Templates > postbit_groupimage
	
Append the following to the end of:
* member_profile_groupimage: ' id="postbit_userbar_{$memprofile['uid']}" />'
* postbit_groupimage: ' id="postbit_userbar_{$post['uid']}" />'
	
Add the following anywhere in:
* headerinclude: '&lt;link rel="stylesheet" href="./inc/plugins/ubhue/ubhue_style.php" />'
	
# Changes
1. Fixed import issues by switching to relative filepaths from the DOCUMENT_ROOT value from the server superglobal variable in PHP.
2. Included the ubhue_style.php file which will handle the CSS for the plugin.