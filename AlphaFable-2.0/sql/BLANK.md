<h1>SQLite Database Area</h1>

This folder will be separate from the site files to prevent direct access to the SQLite database files from the website.

You never want to allow visitors to the site access to these files. The blank *index.html* file is there to prevent the user from seeing a directory listing of the database files.

I'll implement a method of obscuring the database filenames in the installer to make it more difficult for someone to gain direct access in case the *SQL* folder is accessible from the site.
