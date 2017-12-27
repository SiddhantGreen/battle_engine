#ifndef STAT_BOOST_INFO_H_
#define STAT_BOOST_INFO_H_

#define STORE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD(inflicting_bank, is_negative, amount) ((inflicting_bank << 8) | (is_negative << 4) | (amount))

#define RETRIEVE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD() \
                u8 inflicting_bank = acb->data_ptr >> 8;\
                bool is_negative = acb->data_ptr >> 4;\
                u8 amount = acb->data_ptr & 7

#define STORE_STAT_BOOST_MOD_RESULT(is_negative, amount) ((is_negative << 4) | (amount))

#define RETRIEVE_STAT_BOOST_MOD_RESULT(result) \
                bool is_negative = result >> 4;\
                u8 mod_amount = result & 7


#endif /* STAT_BOOST_INFO_H_ */
