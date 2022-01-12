// Copyright (c) 2020 TBP developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef moonet_SMTPUTILS_H
#define moonet_SMTPUTILS_H

#include <string>

namespace smtp {
    bool sendEmail(const std::string& sender,
                   const std::string& recipient,
                   const std::string& smtpUrl,
                   const std::string& smtpUser,
                   const std::string& smtpPass,
                   const std::string& subject,
                   const std::string& body);
}

#endif //moonet_SMTPUTILS_H