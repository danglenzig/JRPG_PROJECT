sync up the feature branch one last time
from the feature branch...
1. `git add *`
2. `git commit -m "Last commit before merging"`
3. `git push`

 pull the current dev into your local dev
1. `git switch main`
2. `git pull`

pull your local dev into your feature branch
1. `git switch feature/branch-name`
2. `git merge main`

pull your feature branch into dev
1. `git switch main`
2. `git pull`
3. `git merge feature/branch-name`

now push it. push it real good
1. `git push`

now create and publish a new branch from here
1. `git switch -c feature/new-feature-branch`
2. `git push -u origin feature/new-feature-branch`