[![Build Status][build-status-img]][travis-ci]

## What is mruby

mruby is the lightweight implementation of the Ruby language complying to (part
of) the [ISO standard][ISO-standard]. Its syntax is Ruby 2.x compatible.

mruby can be linked and embedded within your application.  We provide the
interpreter program "mruby" and the interactive mruby shell "mirb" as examples.
You can also compile Ruby programs into compiled byte code using the mruby
compiler "mrbc".  All those tools reside in the "bin" directory.  "mrbc" is
also able to generate compiled byte code in a C source file, see the "mrbtest"
program under the "test" directory for an example.

This achievement was sponsored by the Regional Innovation Creation R&D Programs
of the Ministry of Economy, Trade and Industry of Japan.

## How to get mruby

The preview version 3.0.0 of mruby can be downloaded via the following URL: [https://github.com/mruby/mruby/archive/3.0.0-preview.zip](https://github.com/mruby/mruby/archive/3.0.0-preview.zip)

The stable version 2.1.2 of mruby can be downloaded via the following URL: [https://github.com/mruby/mruby/archive/2.1.2.zip](https://github.com/mruby/mruby/archive/2.1.2.zip)

The latest development version of mruby can be downloaded via the following URL: [https://github.com/mruby/mruby/zipball/master](https://github.com/mruby/mruby/zipball/master)

The trunk of the mruby source tree can be checked out with the
following command:

    $ git clone https://github.com/mruby/mruby.git

You can also install and compile mruby using [ruby-install](https://github.com/postmodern/ruby-install), [ruby-build](https://github.com/rbenv/ruby-build) or [rvm](https://github.com/rvm/rvm).

## mruby home-page

The URL of the mruby home-page is: https://mruby.org.

## Mailing list

We don't have a mailing list, but you can use [GitHub issues](https://github.com/mruby/mruby/issues).

## How to compile and install (mruby and gems)

See the [compile.md](https://github.com/mruby/mruby/blob/master/doc/guides/compile.md) file.

## How to Build

To build mruby, execute the following from the project's root directory.

  $ rake TARGET=<target> test

The default `TARGET` is `host`. `TARGET` will be loaded from `target` directory.

Note: `bison` bundled with MacOS is too old to compile `mruby`.
Try `brew install bison` and follow the instuction shown to update
the `$PATH` to compile `mruby`.

## Building documentation

There are two sets of documentation in mruby: the mruby API (generated by yard) and C API (Doxygen)

To build both of them, simply go

    rake doc

You can also view them in your browser

    rake view_api
    rake view_capi

## How to customize mruby (mrbgems)

mruby contains a package manager called *mrbgems*. To create extensions
in C and/or Ruby you should create a *GEM*. For a documentation of how to
use mrbgems consult the file [mrbgems.md](https://github.com/mruby/mruby/blob/master/doc/guides/mrbgems.md).
For example code of how to use mrbgems look into the folder *examples/mrbgems/*.

## License

mruby is released under the [MIT License](https://github.com/mruby/mruby/blob/master/LICENSE).

## Note for License

mruby has chosen a MIT License due to its permissive license allowing
developers to target various environments such as embedded systems.
However, the license requires the display of the copyright notice and license
information in manuals for instance. Doing so for big projects can be
complicated or troublesome.  This is why mruby has decided to display "mruby
developers" as the copyright name to make it simple conventionally.
In the future, mruby might ask you to distribute your new code
(that you will commit,) under the MIT License as a member of
"mruby developers" but contributors will keep their copyright.
(We did not intend for contributors to transfer or waive their copyrights,
Actual copyright holder name (contributors) will be listed in the AUTHORS
file.)

Please ask us if you want to distribute your code under another license.

## How to Contribute

See the [contribution guidelines][contribution-guidelines], and then send a pull
request to <http://github.com/mruby/mruby>.  We consider you have granted
non-exclusive right to your contributed code under MIT license.  If you want to
be named as one of mruby developers, please include an update to the AUTHORS
file in your pull request.

[ISO-standard]: http://www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=59579
[build-status-img]: https://travis-ci.org/mruby/mruby.svg?branch=master
[contribution-guidelines]: https://github.com/mruby/mruby/blob/master/CONTRIBUTING.md
[travis-ci]: https://travis-ci.org/mruby/mruby
