# street-light-simulator [![Build Status](https://travis-ci.org/bbvch/street-light-simulator.svg?branch=master)](https://travis-ci.org/bbvch/street-light-simulator) [![License](https://img.shields.io/badge/license-%20GNU--V3-blue.svg)](./LICENSE) [![Coverage Status](https://coveralls.io/repos/github/bbvch/street-light-simulator/badge.svg?branch=master)](https://coveralls.io/github/bbvch/street-light-simulator?branch=master) [![Documentation](https://img.shields.io/badge/Documentation-%20online-green.svg)](http://street-light-simulator-doc.s3-website-us-west-2.amazonaws.com/)

# What
This is a streetlamp simulator.

You can turn (a picture of) a street lamp on/off over the the local D-BUS.
The application also outputs light values over the D-BUS.
Day and night will change according to a certain, configurable cycle with a quantity of randomness between day and night duration.
The duration of day and night is the same on multiple machines (on every machine night starts at the same second).

# Why

This program is used for a bbv internal workshop in connection with [streetlightd](https://github.com/bbvch/streetlightd).

# Who

This program is authored by [bbv Software Services AG](https://www.bbv.ch).

# Prerequisites

On a fresh Xenial Ubuntu you need to install the following packages:

    qml-module-qtquick2 qml-module-qtquick-controls qml-module-qtquick-dialogs qml-module-qtquick-particles2 qt5-default qtdeclarative5-dev

If you haven't already built gtest you have to install

    cmake libgtest-dev

and compile the library like [this](http://askubuntu.com/questions/145887/why-no-library-files-installed-for-google-test)

# Building

The easiest way is through the Qt creator.
But you may also use qmake as follows:

1. Go in to App or test directory
2. Run
```
    qmake .
    make
```

# License

This program is licensed under the GNU V3 license.


