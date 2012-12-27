//All includes for the project are included
#include"cbcIncludes.h"

//Function init() - initializes the program
void init()
{
	cout<<PROGRAM_NAME<<endl<<PROGRAM_AUTHOR<<endl;
	cout<<PROGRAM_VERSION<<endl<<PROGRAM_ACCESORIES<<endl;
	return;
}

//Function main() - Console streams
int main(int argc, char** argv)
{
	//Initialize the program || Display debug messages.
	init();
	//Initialize global data for the Aria class
	Aria::init();
	// This object parses program options from the command line
	ArArgumentParser parser(&argc, argv);
	// Load some default values for command line arguments from /etc/Aria.args
	// (Linux) or the ARIAARGS environment variable.
	parser.loadDefaultArguments();
	//Create an ArRobot object which represents the robot.
	ArRobot robot;
	// Object that connects to the robot or simulator using program options
	ArRobotConnector robotConnector(&parser, &robot);
	// Connect to the robot, get some initial data from it such as type and name,
	// and then load parameter files for this robot.
	if (!robotConnector.connectRobot())
	{
		// Error connecting:
		// if the user gave the -help argumentp, then just print out what happened,
		// and continue so options can be displayed later.
		if (!parser.checkHelpAndWarnUnparsed())
			ArLog::log(ArLog::Terse, "Could not connect to robot, will not have parameter file so options displayed later may not include everything");
		// otherwise abort
		else
		{
			ArLog::log(ArLog::Terse, "Error, could not connect to robot.");
			Aria::logOptions();
			Aria::exit(1);
		}
	}
	if(!robot.isConnected())
		ArLog::log(ArLog::Terse, "Internal error: robot connector succeeded but ArRobot::isConnected() is false!");
	// Connector for laser rangefinders
	ArLaserConnector laserConnector(&parser, &robot, &robotConnector);
	// Connector for compasses
	ArCompassConnector compassConnector(&parser);
	// Parse the command line options. Fail and print the help message if the parsing fails
	// or if the help was requested with the -help option
	if (!Aria::parseArgs() || !parser.checkHelpAndWarnUnparsed())
	{    
	    Aria::logOptions();
	    Aria::exit(1);
	    return 1;
	}
	// Used to perform actions when keyboard keys are pressed
	ArKeyHandler keyHandler;
	Aria::setKeyHandler(&keyHandler);
	// ArRobot contains an exit action for the Escape key. It also 
	// stores a pointer to the keyhandler so that other parts of the program can
	// use the same keyhandler.
	robot.attachKeyHandler(&keyHandler);
	printf("You may press escape to exit\n");
	// Start the robot task loop running in a new background thread. The 'true' argument means if it loses
	// connection the task loop stops and the thread exits.
	robot.runAsync(true);
	// Connect to the laser(s) if lasers were configured in this robot's parameter
	// file or on the command line, and run laser processing thread if applicable
	// for that laser class.  For the purposes of this demo, add all
	// possible lasers to ArRobot's list rather than just the ones that were
	// connected by this call so when you enter laser mode, you
	// can then interactively choose which laser to use from that list of all
	// lasers mentioned in robot parameters and on command line. Normally,
	// only connected lasers are put in ArRobot's list.
	if(!laserConnector.connectLasers(	false,// continue after connection failures
										false,  // add only connected lasers to ArRobot
										true))    // add all lasers to ArRobot
	{
		printf("Could not connect to lasers... exiting\n");
		Aria::exit(2);
	}
	// Create and connect to the compass if the robot has one.
	ArTCM2 *compass = compassConnector.create(&robot);
	if(compass && !compass->blockingConnect())
		compass = NULL;
	// Sleep for a second so some messages from the initial responses
	// from robots and cameras and such can catch up
	ArUtil::sleep(1000);
	// We need to lock the robot since we'll be setting up these modes
	// while the robot task loop thread is already running, and they 
	// need to access some shared data in ArRobot.
	robot.lock();
	// now add all the modes for this demo
	// these classes are defined in ArModes.cpp in ARIA's source code.
	ArModeLaser laser(&robot, "laser", 'l', 'L');
	ArModeTeleop teleop(&robot, "teleop", 't', 'T');
	ArModeUnguardedTeleop unguardedTeleop(&robot, "unguarded teleop", 'u', 'U');
	ArModeWander wander(&robot, "wander", 'w', 'W');
	// activate the default mode
	teleop.activate();
	// turn on the motors
	robot.comInt(ArCommands::ENABLE, 1);
	robot.unlock();
	// Block execution of the main thread here and wait for the robot's task loop
	// thread to exit (e.g. by robot disconnecting, escape key pressed, or OS
	// signal)
	robot.waitForRunExit();
	Aria::exit(0);
	return 0;
}