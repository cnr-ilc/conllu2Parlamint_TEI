# conllu2Parlamint_TEI
Corpus Parlamint Directory Structure

The starting parliamentary corpus is structurally divided by years, from 2013 to 2020, each of which contains the sessions in TEI XML format. Each session contains sections, motions, information on the speaker on her role, and above all the text of the speeches divided into small narratives contained within the tag. These textual units, which can correspond to different sentences, are the ones that are of interest for the project and have been linguistically analyzed. Each session therefore contains a variable number of segments (50 - 100-150 just to give an order of ideas) with its own unique identifier whose text has been linguistically analyzed producing files in CoNLL-U format.

Corpus Parlamint Linguistically Analyzed Directory Structure

It will therefore appear that each session will have associated a directory of linguistically analyzed files in which number corresponds to the number of segments it contains. The names of the files have meaning since the file corresponding to the session YYY.xml of a certain year containing N segments will correspond to N files contained in the YYY directory and logically identified by the files YYY.seg1.udner, YYY.seg2, udener, … YYY.segN.udner

The program takes as input the list of files of a year, one per line, and assumes that for each file Parlamint_xxxx_sed_n.xml with n = 1,2,3 .... exist a directory Parlamint_xxxx_sed_n with as many segment files as are the segments present in Parlamint_xxxx_sed_n.xml with the constraint of having the name Parlamint_xxxx_sed_n.seg_m.ud.udner with m=1,2,3.... number of segment.
