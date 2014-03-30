/***************************************************************************
 * getaddrinfo.c -- A **PARTIAL** implementation of the getaddrinfo(3)     *
 * hostname resolution call.  In particular, IPv6 is not supported and     *
 * neither are some of the flags.  Service "names" are always returned as  *
 * port numbers.                                                           *
 *                                                                         *
 ***********************IMPORTANT NMAP LICENSE TERMS************************
 *                                                                         *
 * The Nmap Security Scanner is (C) 1996-2013 Insecure.Com LLC. Nmap is    *
 * also a registered trademark of Insecure.Com LLC.  This program is free  *
 * software; you may redistribute and/or modify it under the terms of the  *
 * GNU General Public License as published by the Free Software            *
 * Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE CLARIFICATIONS  *
 * AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your right to use,    *
 * modify, and redistribute this software under certain conditions.  If    *
 * you wish to embed Nmap technology into proprietary software, we sell    *
 * alternative licenses (contact sales@insecure.com).  Dozens of software  *
 * vendors already license Nmap technology such as host discovery, port    *
 * scanning, OS detection, version detection, and the Nmap Scripting       *
 * Engine.                                                                 *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Reads or includes copyrighted data files, such as Nmap's nmap-os-db   *
 * or nmap-service-probes.                                                 *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * Nmap with other software in compressed or archival form does not        *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
 * of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * As another special exception to the GPL terms, Insecure.Com LLC grants  *
 * permission to link the code of this program with any version of the     *
 * OpenSSL library which is distributed under a license identical to that  *
 * listed in the included docs/licenses/OpenSSL.txt file, and distribute   *
 * linked combinations including the two.                                  *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the special and conditions of the license text as well.       *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * Nmap or grant special permissions to use it in other open source        *
 * software.  Please contact fyodor@nmap.org with any such requests.       *
 * Similarly, we don't incorporate incompatible open source software into  *
 * Covered Software without special permission from the copyright holders. *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * Nmap in other works, are happy to help.  As mentioned above, we also    *
 * offer alternative license to integrate Nmap into proprietary            *
 * applications and appliances.  These contracts have been sold to dozens  *
 * of software vendors, and generally include a perpetual license as well  *
 * as providing for priority support and updates.  They also fund the      *
 * continued development of Nmap.  Please email sales@insecure.com for     *
 * further information.                                                    *
 *                                                                         *
 * If you received these files with a written license agreement or         *
 * contract stating terms other than the terms above, then that            *
 * alternative license agreement takes precedence over these comments.     *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes (none     *
 * have been found so far).                                                *
 *                                                                         *
 * Source code also allows you to port Nmap to new platforms, fix bugs,    *
 * and add new features.  You are highly encouraged to send your changes   *
 * to the dev@nmap.org mailing list for possible incorporation into the    *
 * main distribution.  By sending these changes to Fyodor or one of the    *
 * Insecure.Org development mailing lists, or checking them into the Nmap  *
 * source code repository, it is understood (unless you specify otherwise) *
 * that you are offering the Nmap Project (Insecure.Com LLC) the           *
 * unlimited, non-exclusive right to reuse, modify, and relicense the      *
 * code.  Nmap will always be available Open Source, but this is important *
 * because the inability to relicense code has caused devastating problems *
 * for other Free Software projects (such as KDE and NASM).  We also       *
 * occasionally relicense the code to third parties as discussed above.    *
 * If you wish to specify special license conditions of your               *
 * contributions, just say so when you send them.                          *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Nmap      *
 * license file for more details (it's in a COPYING file included with     *
 * Nmap, and also available from https://svn.nmap.org/nmap/COPYING         *
 *                                                                         *
 ***************************************************************************/

/* $Id: getaddrinfo.c 31563 2013-07-28 22:08:48Z fyodor $ */

#include "nbase.h"

#include <stdio.h>
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#if HAVE_NETDB_H
#include <netdb.h>
#endif
#include <assert.h>


#if !defined(HAVE_GAI_STRERROR) || defined(__MINGW32__)
#ifdef __MINGW32__
#undef gai_strerror
#endif

const char *gai_strerror(int errcode) {
  static char customerr[64];
  switch (errcode) {
  case EAI_FAMILY:
    return "ai_family not supported";
  case EAI_NODATA:
    return "no address associated with hostname";
  case EAI_NONAME:
    return "hostname nor servname provided, or not known";
  default:
    Snprintf(customerr, sizeof(customerr), "unknown error (%d)", errcode);
    return "unknown error.";
  }
  return NULL; /* unreached */
}
#endif

#ifdef __MINGW32__
char* WSAAPI gai_strerrorA (int errcode)
{
  return gai_strerror(errcode);
}
#endif

#ifndef HAVE_GETADDRINFO
void freeaddrinfo(struct addrinfo *res) {
  struct addrinfo *next;
  
  do {
    next = res->ai_next;
    free(res);
  } while ((res = next) != NULL);
}

/* Allocates and initializes a new AI structure with the port and IPv4
   address specified in network byte order */
static struct addrinfo *new_ai(unsigned short portno, u32 addr)
{
	struct addrinfo *ai;

	ai = (struct addrinfo *) safe_malloc(sizeof(struct addrinfo) + sizeof(struct sockaddr_in));
	
	memset(ai, 0, sizeof(struct addrinfo) + sizeof(struct sockaddr_in));
	
	ai->ai_family = AF_INET;
	ai->ai_addrlen = sizeof(struct sockaddr_in);
	ai->ai_addr = (struct sockaddr *)(ai + 1);
	ai->ai_addr->sa_family = AF_INET;
#if HAVE_SOCKADDR_SA_LEN
	ai->ai_addr->sa_len = ai->ai_addrlen;
#endif
	((struct sockaddr_in *)(ai)->ai_addr)->sin_port = portno;
	((struct sockaddr_in *)(ai)->ai_addr)->sin_addr.s_addr = addr;
	
	return(ai);
}


int getaddrinfo(const char *node, const char *service, 
		const struct addrinfo *hints, struct addrinfo **res) {

  struct addrinfo *cur, *prev = NULL;
  struct hostent *he;
  struct in_addr ip;
  unsigned short portno;
  int i;
  
  if (service)
    portno = htons(atoi(service));
  else
    portno = 0;
  
  if (hints && hints->ai_flags & AI_PASSIVE) {
    *res = new_ai(portno, htonl(0x00000000));
    return 0;
  }
  
  if (!node) {
    *res = new_ai(portno, htonl(0x7f000001));
    return 0;
  }
  
  if (inet_pton(AF_INET, node, &ip)) {
    *res = new_ai(portno, ip.s_addr);
    return 0;
  }
  
  he = gethostbyname(node);
  if (he && he->h_addr_list[0]) {
    for (i = 0; he->h_addr_list[i]; i++) {
      cur = new_ai(portno, ((struct in_addr *)he->h_addr_list[i])->s_addr);

      if (prev)
	prev->ai_next = cur;
      else
	*res = cur;
      
      prev = cur;
    }
    return 0;
  }
  
  return EAI_NODATA;
}
#endif /* HAVE_GETADDRINFO */