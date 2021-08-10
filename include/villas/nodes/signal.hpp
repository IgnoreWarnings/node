/** Node-type for signal generation.
 *
 * @file
 * @author Steffen Vogel <stvogel@eonerc.rwth-aachen.de>
 * @copyright 2014-2021, Institute for Automation of Complex Power Systems, EONERC
 * @license GNU General Public License (version 3)
 *
 * VILLASnode
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************************/

#pragma once

#include <villas/timing.hpp>
#include <villas/task.hpp>
#include <villas/node.hpp>

namespace villas {
namespace node {

/* Forward declarations */
struct Sample;

class SignalNodeSignal {

public:
	enum class Type {
		RANDOM,
		SINE,
		SQUARE,
		TRIANGLE,
		RAMP,
		COUNTER,
		CONSTANT,
		PULSE,
		MIXED
	};

	enum Type type;

	double frequency;		/**< Frequency of the generated signals. */
	double amplitude;		/**< Amplitude of the generated signals. */
	double stddev;			/**< Standard deviation of random signals (normal distributed). */
	double offset;			/**< A constant bias. */
	double pulse_width;		/**< Width of a pulse with respect to the rate (duration = pulse_width/rate) */
	double pulse_low;		/**< Amplitude when pulse signal is off */
	double pulse_high;		/**< Amplitude when pulse signal is on */
	double phase;			/**< Phase (rad) offset with respect to program start */
	double last;			/**< The values from the previous period which are required for random walk. */

public:
	SignalNodeSignal(json_t *json);

	int parse(json_t *json);

	static
	enum Type lookupType(const std::string &type);

	static
	std::string typeToString(enum Type type);

	void start();

	void read(unsigned c, double t, double rate, SignalData *d);

	Signal::Ptr toSignal(Signal::Ptr tpl) const;
};

class SignalNode : public Node {

protected:
	std::vector<SignalNodeSignal> signals;

	struct Task task;			/**< Timer for periodic events. */
	int rt;					/**< Real-time mode? */

	double rate;				/**< Sampling rate. */
	bool monitor_missed;			/**< Boolean, if set, node counts missed steps and warns user. */
	int limit;				/**< The number of values which should be generated by this node. <0 for infinite. */

	struct timespec started;		/**< Point in time when this node was started. */
	unsigned missed_steps;			/**< Total number of missed steps. */

public:
	SignalNode(const std::string &name = "");

	virtual
	const std::string & getDetails();

	virtual
	int parse(json_t *json, const uuid_t sn_uuid);

	virtual
	int start();

	virtual
	int stop();

	virtual
	int prepare();

	virtual
	int _read(struct Sample *smps[], unsigned cnt);

	virtual
	std::vector<int> getPollFDs();
};

} /* namespace node */
} /* namespace villas */
