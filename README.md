# Configure SSH access
## Add the SSH key 
```
$ ssh-add /c/mazerunner/.ssh/id_ed25519
Could not open a connection to your authentication agent.
```
## Troubleshooting
### Could not open a connection to your authentication agent
Check whether the authentication agent is running
```
$ ssh-agent
SSH_AUTH_SOCK=/tmp/ssh-eHy5FfISVnNG/agent.424; export SSH_AUTH_SOCK;
SSH_AGENT_PID=425; export SSH_AGENT_PID;
echo Agent pid 425;
```
Retrieve the PID for the authentication agent process
```
$ eval $(ssh-agent)
Agent pid 430
```
Try adding the SSH key again
```
$ ssh-add /c/mazerunner/.ssh/id_ed25519
Identity added: /c/mazerunner/.ssh/id_ed25519 (mazerunner.latam@gmail.com)
```
A git command like clonning a repository should work now
```
$ git clone git@github.com:mazerunnerlatam/webots.git
Cloning into 'webots'...
warning: You appear to have cloned an empty repository.
```