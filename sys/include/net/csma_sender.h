/*
 * Copyright (C) 2015 INRIA
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    net_csma_sender  CSMA/CA helper
 * @ingroup     net
 * @brief       This interface allows code from layer 2 (MAC) or higher
 *              to send packets with CSMA/CA, whatever the abilities and/or
 *              configuration of a given radio transceiver device are.
 * @{
 *
 * @file
 * @brief       Interface definition for the CSMA/CA helper
 *
 * @author      Kévin Roussel <Kevin.Roussel@inria.fr>
 */

#ifndef CSMA_SENDER_H_
#define CSMA_SENDER_H_

#include <stdint.h>

#include "net/netdev2.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Default Minimal CSMA/CA Backoff Exponent
 */
#define CSMA_SENDER_MIN_BE_DEFAULT          (3U)

/**
 * @brief Default Maximal CSMA/CA Backoff Exponent
 */
#define CSMA_SENDER_MAX_BE_DEFAULT          (5U)

/**
 * @brief Default Maximal number of retries for sending
 *        a given packet with the CSMA/CA method
 */
#define CSMA_SENDER_MAX_BACKOFFS_DEFAULT    (4U)

/**
 * @brief CSMA/CA backoff period, in microseconds
 */
#define CSMA_SENDER_BACKOFF_PERIOD_UNIT     (320U)

/**
 * @brief Define a different (non-standard) value for
 *        the CSMA macMinBE parameter.
 *
 * @param[in] val     new value for macMinBE
 */
void csma_sender_set_min_be(uint8_t val);

/**
 * @brief Define a different (non-standard) value for
 *        the CSMA macMaxBE parameter.
 *
 * @param[in] val     new value for macMaxBE
 */
void csma_sender_set_max_be(uint8_t val);

/**
 * @brief Define a different (non-standard) value for
 *        the CSMA macMaxCSMABackoffs parameter.
 *
 * @param[in] val     new value for macMaxCSMABackoffs
 */
void csma_sender_set_max_backoffs(uint8_t val);

/**
 * @brief   Sends a 802.15.4 frame using the CSMA/CA method
 *
 * @pre `dev != NULL`
 *
 * If the transceiver can (and is configured to) do hardware-assisted
 * CSMA/CA, this feature is used. Otherwise, a software procedure is used.
 *
 * @param[in] dev       netdev device, needs to be already initialized
 * @param[in] vector    pointer to the data
 * @param[in] count     number of elements in @p vector
 *
 * @return              number of bytes that were actually send out
 * @return              -ENODEV if @p dev is invalid
 * @return              -ENOMSG if @p pkt is invalid
 * @return              -EOVERFLOW if the payload size of @p pkt exceeds the
 *                      payload size that can be handled by the device
 * @return              -ECANCELED if an internal driver error occured
 * @return              -EBUSY if radio medium never was available
 *                      to send the given data
 */
int csma_sender_csma_ca_send(netdev2_t *dev, struct iovec *vector,
                             unsigned count);

/**
 * @brief   Sends a 802.15.4 frame when medium is avaiable.
 *
 * @pre `dev != NULL`
 *
 * This function is useful for sending packets without the whole CSMA/CA
 * procedure, but *after* ensuring medium is available, that is after a
 * successful CCA.
 *
 * It is especially useful for broadcasting specific packets, like beacons; or
 * for many sending packets in burst.
 *
 * @warning **ATTENTION:** It only tries to send the given data once. If you
 *          want the complete CSMA/CA procedure with retries, use
 *          @ref csma_sender_csma_ca_send().
 *
 * @param[in] dev       netdev device, needs to be already initialized
 * @param[in] vector    pointer to the data
 * @param[in] count     number of elements in @p vector
 *
 * @return              number of bytes that were actually send out
 * @return              -ENODEV if @p dev is invalid
 * @return              -ENOMSG if @p pkt is invalid
 * @return              -EOVERFLOW if the payload size of @p pkt exceeds the
 *                      payload size that can be handled by the device
 * @return              -ECANCELED if an internal driver error occured
 * @return              -EBUSY if radio medium was not available
 *                      to send the given data
 */
int csma_sender_cca_send(netdev2_t *dev, struct iovec *vector, unsigned count);


#ifdef __cplusplus
}
#endif

#endif /* CSMA_SENDER_H_ */

/** @} */
