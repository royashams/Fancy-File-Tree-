# Fancy-File-Tree-
A program written in C for a "Software Tools and Systems Programming" course, The goal of this assignment was to
reproduce something similar that prints out a file tree. It looks recursively at folders and files and prints them in a 
specific format, and also lists the permissions within it as well. This project was completed in March of 2017.

Try this on any file or directory, especially if it has more directorie within!
In your terminal, write the following

>>> make

>>> ./print_ftree your_file_here

And watch the magic happen! just replace your_file_here with any file or directory.

I've included a sample directory called "Sushi" for demonstration. It produces the following result:

===== Sushi (755) =====
  ===== Empty (755) =====
  Ginger.rtf (644)
  justine.jpg (644)
  link1 (755)
  ===== Permissions (770) =====
    Meat.jpg (644)
  ===== Rolls (755) =====
    ===== California (755) =====
      Avocado.rtf (644)
      Book Cover @Roya.jpg (600)
      fish eggs.rtf (644)
      rice.rtf (644)
      tester (644)
    Dynamite.rtf (644)
    gmo comic.jpg (644)
    ===== Hand Rolls (755) =====
      Cone Shape.rtf (644)
      egg rolls? .rtf (644)
  ===== Sashimi (755) =====
    ===== Crab (755) =====
    Salmon.rtf (644)
    White Fish.rtf (644)
  Seaweed.rtf (644)
  ===== Single (755) =====
    Ginger.rtf (644)
    gmocomic.jpg (644)


