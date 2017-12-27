#ifndef STAT_BOOST_INFO_H_
#define STAT_BOOST_INFO_H_

#define STORE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD(macro_param_inflicting_bank, macro_param_is_negative, macro_param_amount) ((macro_param_inflicting_bank << 8) | (macro_param_is_negative << 4) | (macro_param_amount))

#define RETRIEVE_ADDITIONAL_DATA_FOR_STAT_BOOST_MOD() \
                u8 macro_param_inflicting_bank = acb->data_ptr >> 8;\
                bool macro_param_is_negative = acb->data_ptr >> 4;\
                u8 macro_param_amount = acb->data_ptr & 7

#define STORE_STAT_BOOST_MOD_RESULT(macro_param_is_negative, macro_param_amount) ((macro_param_is_negative << 4) | (macro_param_amount))

#define RETRIEVE_STAT_BOOST_MOD_RESULT(macro_param_result) \
                bool macro_param_is_negative = macro_param_result >> 4;\
                u8 macro_param_mod_amount = macro_param_result & 7


#endif /* STAT_BOOST_INFO_H_ */
