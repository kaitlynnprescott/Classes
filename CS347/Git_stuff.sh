#clone the git repo, creates a directory "tie-breaker" that has all the stuff in it
git clone http://git.4sense.eu:9191/joshgrib/tie-breaker.git

#from here on everything is in the "tie-breaker" directory

#get any changes from the server, update your files
git pull

#make any edits you want

#see what you changed
git diff

#"stage" a file - choose what to commit
git add <filename>

#unstage
git rm <filename>

#add all files that were changed, this is what I usually do
git add --all

#commit changes to your local repo
#the commit message should cover what you did in this change in a sentance
git commit -am "<commit message>"

#send your commits to the server
git push
#then enter your email and password for git.4sense.eu

#This is my usualy workflow, but there's other ways to do stuff and there's a lot more features but I don't usually need branches or anything so I don't know them well