/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    AbstractMutex.h
/// @author  Daniel Krajzewicz
/// @author  Michael Behrisch
/// @date    2005-07-12
/// @version $Id$
///
// An abstract class for encapsulating mutex implementations
/****************************************************************************/
#ifndef AbstractMutex_h
#define AbstractMutex_h


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class AbstractMutex
 * @brief An abstract class for encapsulating mutex implementations
 *
 * This class defines access to a mutex. The implementation may differ.
 *
 * Within gui-applications, FXMutexes may be used while this is improper
 *  for command-line applications. Normally, they do not need mutexes unless
 *  a synchronized communication with an external application is established.
 *  In these cases, a further class should be implemented.
 */
class AbstractMutex {
public:
    /// @brief Constructor
    AbstractMutex() { }


    /// @brief Destructor
    virtual ~AbstractMutex() { }


    /// @brief Locks the mutex
    virtual void lock() = 0;


    /// @brief Unlocks the mutex
    virtual void unlock() = 0;



    /** @class ScopedLocker
     * @brief A mutex encapsulator which locks/unlocks the given mutex on construction/destruction, respectively
     */
    class ScopedLocker {
    public:
        /** @brief Constructor
         * @param[in] lock The mutex to lock
         *
         * Locks the mutex.
         */
        ScopedLocker(AbstractMutex& lock): myLock(lock) {
            myLock.lock();
        }


        /** @brief Destructor
         * Unlocks the mutex.
         */
        ~ScopedLocker() {
            myLock.unlock();
        }

    private:
        /// @brief The mutex to lock
        AbstractMutex& myLock;

    private:
        /// @brief Invalidated copy constructor.
        ScopedLocker(const ScopedLocker&);

        /// Invalidated assignment operator.
        ScopedLocker& operator=(const ScopedLocker&);


    };



};


#endif

/****************************************************************************/

