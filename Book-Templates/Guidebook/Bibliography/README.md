## Guidebook Template

```
Author:	Dracovian
Date: 	July 16, 2019

This portion of the Guidebook Template is reserved
for any bibliographies and articles (bibTeX).

To use bibTeX you must ensure that the natbib
package is in use.

We can create our bibliographies by creating a file
with a .bib filetype with the following contents:

@Article{Article_Name,
	author = {Author Name},
	title = {Article Title},
	journal = {Journal Name},
	Month = jan,
	Year = 1901,
	Volume = 1,
	Pages = {1--50}}

@InProceedings{Proceeding_Name,
	author = {Author Name},
	title = {Proceedings Title},
	booktitle = {Book Title},
	Month = jan,
	Year = 1901}
	
Then we can add our bibliographies into our book
using these commands:

\citep[args]{Article_Name}
\citet[args]{Proceeding_Name}

\bibliography[args]{Bibliography/Filename}
\bibliographystyle[args]{stylename}
```