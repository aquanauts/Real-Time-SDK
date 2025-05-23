VANiProvider Application Description

--------
Summary:
--------

The purpose of this application is to demonstrate non-interactively providing
Level I Market Price and Level 2 Market By Order data to an Advanced Data Hub(ADH)
using ValueAdd components. It is a single-threaded client application.

The consumer application implements callbacks that process information received
by the ADH. It creates the Reactor, creates the desired connections, then
dispatches from the Reactor for events and messages. Once it has received the
event indicating that the channel is ready, it begins sending refresh and update
messages for the given items.

This application is intended as a basic usage example. Some of the design choices
were made to favor simplicity and readability over performance. This application
is not intended to be used for measuring performance.

-----------------
Application Name:
-----------------

VANiProvider

------------------
Setup Environment:
------------------

The RDMFieldDictionary and enumtype.def files located in the etc directory
must be located in the directory of execution. If the dictionary files
cannot be found, the non-interactive provider application exits.

-------------------
Command line usage:
-------------------

dotnet run -- [-c <hostname>:<port> <service name> <domain>:<item name>,...] [-bc <hostname>:<port>] [-uname <LoginUsername>] [-view] [-post] [-offpost] [-snapshot] [-runtime <seconds>]

The items list is a comma-separated pair of <domain:item name>.  The domains for the item
list may be any of: mp(MarketPrice), mbo(MarketByOrder)

Specifying the -runtime option controls the time the application will run
before exiting, in seconds.

Specifying the -at option configures the token used for UserAuthn Authentication. This should be used
in place of a userName.  This token is retrieved from a token generator, and passed to
LSEG Real-Time Distribution, which will verify the token against a token validator.
For more information about the UserAuthn Authentication feature, please see the Developers guide and
the UserAuthn Authentication guide.

Specifying the -ax option configures the authentication extended information used for UserAuthn Authentication.

Specifying the -aid option configures the Application Id.

To view all command-line options, run:

dotnet run -- -?

Pressing the Ctrl+C buttons terminates the program.

-----------------
Compiling Source:
-----------------

The included project file is set up to run from the file locations as presented
through the distribution package.

To compile, run the `dotnet build` command with desired parameters
(configuration, architecture, etc.)

For windows platform, using Visual Studio, open the main ETA.NET.sln solution
file and build the VANiProvider project.

----------------
Example Content:
----------------

Included for this application are:

- Source files.

- This document.

--------------------
Detailed Description
--------------------

VANiProvider.cs - The main file for the rsslVANIProvider application.

MarketPriceHandler.cs - Contains code used for generating Market Price content.

MarketByOrderHandler.cs - Contains code used for generating Market By Order content.
