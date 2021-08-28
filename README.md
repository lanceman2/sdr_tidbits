# sdr_tidbits

Odds and ends, tid bits of code that may be used for Software Defined
Radio (SDR).

Just some demo programs we can run.  We don't explain so much.

Some parts of this package may get tagged (git) and pulled into other
projects/packages using the github web API.  It's a very modular and
distributed way of developing and sharing code without the nasty
side-effects that come about from code replication.  And as everybody
knows, code replication is not a problem if code is stable.  Maybe I need
to look into one of those web distributed software build systems, or
better yet use Nix builds.

This code is being developed on GNU/Linux systems like Ubuntu 20.04.

## Dependencies (auto depend)

We try to make dependencies be self evident for programming experts; like
for example if there is a make warning that says can't find library "foo"
so not making "bar", than if you need bar, than you need foo; otherwise
move on without using bar without error, and just ignore that 'make'
warning.

