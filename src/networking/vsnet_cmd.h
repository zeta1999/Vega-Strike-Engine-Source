/* 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef VSNET_CMD_H
#define VSNET_CMD_H

#include <iostream>

/// Commands that are sent through the network
enum Cmd
{
	// Login commands
    CMD_LOGIN        = 0x01,	// Client side : login request sent to server with name and passwd
    CMD_LOGOUT       = 0xA1,	// Client side : tells the server we are logging out
								// Server side : remove the client from the game
    LOGIN_ERROR      = 0xF1,	// Packet sent from account server to client : a login error (mostly bad name/passwd)
    LOGIN_ACCEPT     = 0xF0,	// Packet sent from account server to client : login accepted
    LOGIN_ALREADY    = 0xF6,	// Packet sent from account server to client to tell account is already being used
    LOGIN_NEW        = 0xF7,
	LOGIN_UNAVAIL	 = 0xF9,	// Packet sent from game server to client : account server is unavailable -> no login

	// Character creation stuff (not used yet)
    CMD_NEWCHAR      = 0x04,		// NOT USED : should get the new character description for new account
    CMD_INITIATE     = 0x02,		// NOT USED : should send starting locations for new account
    CMD_CREATECHAR   = 0x50,
    CMD_LOCATIONS    = 0x51,

	// Commands used to add/remove ships in systems
    CMD_LETSGO       = 0x05,		// NOT USED
    CMD_ADDCLIENT    = 0x07,		// Client side : request the server to be added in the game
									// Server side : adds the client to the game
    CMD_ENTERCLIENT  = 0xF2,		// (Server -> Client) Indicates that a new client is entering the current zone
									// also send the new client's data
    CMD_EXITCLIENT   = 0xF3,		// (Server -> Client) Indicates that a client is leaving the current zone
    CMD_ADDEDYOU     = 0xF5,		// NOT USED

	// Ships movements data
    CMD_POSUPDATE    = 0x03,		// On client side (send): containing a ship's data sent to server for position update
									// On client side (recv) : receive minimal update data for a ship
									// On server side : sending minimal info (just position) in case the ship is far from
									// the one we send other ships' data to
    CMD_UPDATECLT    = 0x06,
    CMD_FULLUPDATE   = 0x08,		// On client side (recv) : receive full update info for a ship
    CMD_PING         = 0x09,		// A packet sending a ping-like command just to tell to the server
									// that the client is still alive
    CMD_SNAPSHOT     = 0xA0,		// A packet with all the necessary ships' data in order to update

	// Weapons commands
	CMD_FIREREQUEST  = 0x94,		// Fire Request
	CMD_UNFIREREQUEST= 0x95,		// UnFire Request
	CMD_BOLT         = 0x90,		// Fire a bolt
	CMD_BEAM         = 0x91,		// Fire a beam
	CMD_PROJECTILE   = 0x92,        // Fire a projectile
	CMD_BALL         = 0x93,		// Fire a ball ?
	CMD_TARGET       = 0x96,		// Receive a target request (server side) or receive target info (client side)
	CMD_SCAN         = 0x97,		// Receive a scan request (server side) or receive target info (client side)

	// Account management commands
	CMD_RESYNCACCOUNTS = 0xFA,		// When connection to account server was lost and established again :
									// send the account server a list of active client to sync and log out
									// client that may have quit the game during loss of connection
	CMD_SAVEACCOUNTS = 0xFB,		// Send a client save to account server in order to do a backup
    CMD_NEWSUBSCRIBE = 0x40,		// Account server : handle a new account creation (login/passwd) on the web

    CMD_DISCONNECT   = 0xF4,		// UDP : after a problem (not clean exit) to make the client exit if still alive

    CMD_ACK          = 0xFF			// A packet to acknoledge the reception of a packet that was previously sent
};

std::ostream& operator<<( std::ostream& ostr, Cmd cmd );

const char* displayCmd( Cmd cmd );

#endif

