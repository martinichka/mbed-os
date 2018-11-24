/* mbed Microcontroller Library
 * Copyright (c) 2018-2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef MBED_GAP_SCAN_PARAMETERS_H__
#define MBED_GAP_SCAN_PARAMETERS_H__

#include <stdint.h>
#include "ble/blecommon.h"
#include "BLETypes.h"

/**
 * @addtogroup ble
 * @{
 * @addtogroup gap
 * @{
 */

namespace ble {

class ScanParameters {
public:

    /**
     * Scan configuration of a physical channel.
     */
    struct phy_configuration_t {
        /**
         * Construct a phy_configuration_t.
         * @param scan_interval The scan interval.
         * @param scan_window The scan window
         * @param active_scanning True if scan request should be sent and false
         * otherwise.
         */
        phy_configuration_t(
            scan_interval_t scan_interval = scan_interval_t::min(),
            scan_window_t scan_window = scan_window_t::min(),
            bool active_scanning = false
        ) :
            interval(scan_interval),
            window(scan_window),
            active_scanning(active_scanning)
        {
            if (window.value() > interval.value()) {
                interval = window;
            }
        }

        /**
         * Get the scan interval.
         */
        const scan_window_t &getInterval() const
        {
            return interval;
        }

        /**
         * Get the scan window.
         */
        const scan_interval_t &getWindow() const
        {
            return window;
        }

        /**
         * Return if active scanning is set.
         */
        bool isActiveScanningSet() const
        {
            return active_scanning;
        }

    private:
        scan_window_t interval;
        scan_interval_t window;
        bool active_scanning;
    };

    /**
     * Construct a ScanParameters object that operate on a selected phy.
     *
     * @param phy The phy to configure.
     * @param scan_interval The scan interval.
     * @param scan_window The scan window.
     * @param active_scanning active scanning flag
     * @param own_address_type Address type used in scan requests.
     * @param scanning_filter_policy Filter applied.
     */
    ScanParameters(
        phy_t phy = phy_t::LE_1M,
        scan_window_t scan_interval = scan_interval_t::min(),
        scan_interval_t scan_window = scan_window_t::min(),
        bool active_scanning = false,
        own_address_type_t own_address_type = own_address_type_t::PUBLIC,
        scanning_filter_policy_t scanning_filter_policy = scanning_filter_policy_t::NO_FILTER
    ) :
        own_address_type(own_address_type),
        scanning_filter_policy(scanning_filter_policy),
        phys(phy),
        phy_1m_configuration(),
        phy_coded_configuration()
    {
        phy_configuration_t conf(scan_interval, scan_window, active_scanning);
        if (phy == phy_t::LE_1M) {
            phy_1m_configuration = conf;
        } else if (phy == phy_t::LE_CODED) {
            phy_coded_configuration = conf;
        }
    }

    ScanParameters &setOwnAddressType(own_address_type_t address)
    {
        own_address_type = address;
        return *this;
    }

    own_address_type_t getOwnAddressType() const
    {
        return own_address_type;
    }

    ScanParameters &setFilter(scanning_filter_policy_t filter_policy)
    {
        scanning_filter_policy = filter_policy;
        return *this;
    }

    scanning_filter_policy_t getFilter() const
    {
        return scanning_filter_policy;
    }

    ScanParameters &setPhys(bool enable_1m, bool enable_coded)
    {
        phys.set_1m(enable_1m);
        phys.set_coded(enable_coded);
        return *this;
    }

    phy_set_t getPhys() const
    {
        return phys;
    }

    ScanParameters &set1mPhyConfiguration(
        scan_interval_t interval,
        scan_window_t window,
        bool active_scanning
    )
    {
        phys.set_1m(true);
        phy_1m_configuration = phy_configuration_t(
            interval, window, active_scanning
        );
        return *this;
    }

    phy_configuration_t get1mPhyConfiguration() const
    {
        return phy_1m_configuration;
    }

    ScanParameters &setCodedPhyConfiguration(
        scan_interval_t interval,
        scan_window_t window,
        bool active_scanning
    )
    {
        phys.set_coded(true);
        phy_coded_configuration = phy_configuration_t(
            interval, window, active_scanning
        );
        return *this;
    }

    phy_configuration_t getCodedPhyConfiguration() const
    {
        return phy_1m_configuration;
    }

private:
    own_address_type_t own_address_type;
    scanning_filter_policy_t scanning_filter_policy;

    phy_set_t phys;

    phy_configuration_t phy_1m_configuration;
    phy_configuration_t phy_coded_configuration;
};

} // namespace ble

/**
 * @}
 * @}
 */

#endif /* ifndef MBED_GAP_SCAN_PARAMETERS_H__ */
