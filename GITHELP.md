sync up the feature branch one last time
from the feature branch...
`git add *`
`git commit -m "Last commit before merging"`
`git push`

 pull the current dev into your local dev
`git switch main`
`git pull`

pull your local dev into your feature branch
`git switch feature/branch-name`
`git merge main`

pull your feature branch into dev
`git switch main`
`git pull`
`git merge feature/branch-name`

now push it. push it real good
`git push`

now create and publish a new branch from here
`git switch -c feature/new-feature-branch`
`git push -u origin feature/new-feature-branch`