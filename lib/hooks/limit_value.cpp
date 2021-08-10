/** Limit hook.
 *
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

#include <bitset>

#include <cstring>

#include <villas/hook.hpp>
#include <villas/node/exceptions.hpp>
#include <villas/signal.hpp>
#include <villas/sample.hpp>

namespace villas {
namespace node {

class LimitValueHook : public MultiSignalHook {

protected:
	unsigned offset;

	float min, max;

public:
	LimitValueHook(Path *p, Node *n, int fl, int prio, bool en = true) :
		MultiSignalHook(p, n, fl, prio, en),
		offset(0),
		min(0),
		max(0)
	{ }

	virtual void parse(json_t *json)
	{
		int ret;
		json_error_t err;

		assert(state != State::STARTED);

		MultiSignalHook::parse(json);

		ret = json_unpack_ex(json, &err, 0, "{ s: f, s: f }",
			"min", &min,
			"max", &max
		);
		if (ret)
			throw ConfigError(json, err, "node-config-hook-average");

		state = State::PARSED;
	}

	virtual Hook::Reason process(struct Sample *smp)
	{
		assert(state == State::STARTED);

		for (auto index : signalIndices) {
			switch (sample_format(smp, index)) {
				case SignalType::INTEGER:
					if (smp->data[index].i > max)
						smp->data[index].i = max;

					if (smp->data[index].i < min)
						smp->data[index].i = min;
					break;

				case SignalType::FLOAT:
					if (smp->data[index].f > max)
						smp->data[index].f = max;

					if (smp->data[index].f < min)
						smp->data[index].f = min;
					break;

				case SignalType::INVALID:
				case SignalType::COMPLEX:
				case SignalType::BOOLEAN:
					return Hook::Reason::ERROR; /* not supported */
			}
		}

		return Reason::OK;
	}
};

/* Register hook */
static char n[] = "limit_value";
static char d[] = "Limit signal values";
static HookPlugin<LimitValueHook, n , d, (int) Hook::Flags::PATH | (int) Hook::Flags::NODE_READ | (int) Hook::Flags::NODE_WRITE> p;

} /* namespace node */
} /* namespace villas */
