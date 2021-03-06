#---------------------------------------------------------------------
# @file   log_check.pl
# @author Marcel Smit
#
# @copyright Copyright (c) Remedy IT Expertise BV
#---------------------------------------------------------------------
eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
     & eval 'exec perl -S $0 $argv:q'
     if 0;

# -*- perl -*-

$status = 0;

$found = 0;
$expected = 32;

sub check_policy_count
{
    my $line = shift;
    print $line;
    if ($line =~ "DDS::PRESENTATION_QOS_POLICY_ID" &&
        $line =~ "count=5")
    {
      return 1;
    }
  return 0;
}

# Check the instance handle, returns 1 in case of ok, 0 in case of a failure
sub check_instance_handle
{
    my $line = shift;
    if ($line =~ /\Q{0X10203,0X4050607,0X8090A0B,0XC0D0E0F}\E/ )
    {
      return 1;
    }
    if ($line =~ /\Q{1234567}\E/ )
    {
      return 1;
    }
  return 0;
}


print "Log output:\n";
print ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
open (FILE, "<", @ARGV[0]);
while (my $line = <FILE>)
{
    print $line;
    if ($line =~ "Logging QosPolicyCountSeq")
    {
        $start_found = $found;
        $found=$found+check_policy_count($line);
        $found=$found+check_policy_count($line);
        $found=$found+check_policy_count($line);
        if ($start_found+3 != $found)
        {
            print "ERROR: Error in QosPolicyCountSeq logging detected\n";
        }
    }
    elsif ($line =~ "Logging QosPolicyCount")
    {
        $start_found = $found;
        $found=$found+check_policy_count($line);
        if ($start_found+1 != $found)
        {
            print "ERROR: Error in QosPolicyCount logging detected\n";
        }
    }
    elsif ($line =~ "Logging Time_t")
    {
        if ($line =~ /1970-01-01 0[0-9]:00:15/)
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in Time_t logging detected\n";
        }
    }
    elsif ($line =~ "Logging StatusKind")
    {
        if ($line =~ "DDS::LIVELINESS_LOST_STATUS")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in StatusKind logging detected\n";
        }
    }
    elsif ($line =~ "Logging InstanceHandle_t")
    {
        if (check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in InstanceHandle_t logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::Entity")
    {
        if (check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::Entity logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::SampleLostStatus")
    {
        if ($line =~ "total_count=5" && $line =~ "total_count_change=10")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::SampleLostStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::RequestedDeadlineMissedStatus")
    {
        if ($line =~ "total_count=6" && $line =~ "total_count_change=11" &&
            $line =~ "last_instance_handle=" &&
            check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::RequestedDeadlineMissedStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::InconsistentTopicStatus")
    {
        if ($line =~ "total_count=10" && $line =~ "total_count_change=15")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::InconsistentTopicStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::SampleRejectedStatus")
    {
        if ($line =~ "total_count=15" && $line =~ "total_count_change=20" &&
            $line =~ "REJECTED_BY_SAMPLES_LIMIT" &&
            check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::SampleRejectedStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::OfferedDeadlineMissedStatus")
    {
        if ($line =~ "total_count=7" && $line =~ "total_count_change=12" &&
            $line =~ "last_instance_handle=" &&
            check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::OfferedDeadlineMissedStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::RequestedIncompatibleQosStatus")
    {
        $start_found = $found;
        if ($line =~ "total_count=11" && $line =~ "total_count_change=16" &&
            $line =~ "last_policy_id=DDS::ENTITYFACTORY_QOS_POLICY_ID")
        {
            $found=$found+1;
        }
        $found=$found+check_policy_count($line);
        $found=$found+check_policy_count($line);
        $found=$found+check_policy_count($line);
        if ($start_found + 4 != $found)
        {
            print "ERROR: Error in DDS::RequestedIncompatibleQosStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::OfferedIncompatibleQosStatus")
    {
        $start_found = $found;
        if ($line =~ "total_count=12" && $line =~ "total_count_change=17" &&
            $line =~ "last_policy_id=DDS::READERDATALIFECYCLE_QOS_POLICY_ID")
        {
            $found=$found+1;
        }
        $found=$found+check_policy_count($line);
        $found=$found+check_policy_count($line);
        $found=$found+check_policy_count($line);
        if ($start_found + 4 != $found)
        {
            print "ERROR: Error in DDS::OfferedIncompatibleQosStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::PublicationMatchedStatus")
    {
        if ($line =~ "total_count=20" && $line =~ "total_count_change=15" &&
            $line =~ "current_count=12" && "current_count_change=7" &&
            $line =~ "last_subscription_handle=" &&
            check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::PublicationMatchedStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::SubscriptionMatchedStatus")
    {
        if ($line =~ "total_count=7" && $line =~ "total_count_change=12" &&
            $line =~ "current_count=15" && "current_count_change=20" &&
            $line =~ "last_publication_handle=" &&
            check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::SubscriptionMatchedStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::LivelinessLostStatus")
    {
        if ($line =~ "total_count=8" && $line =~ "total_count_change=13")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::LivelinessLostStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::LivelinessChangedStatus")
    {
        if ($line =~ "alive_count=9" && $line =~ "not_alive_count=14" &&
            $line =~ "alive_count_change=16" && $line =~ "not_alive_count_change=21" &&
            $line =~ "last_publication_handle=" &&
            check_instance_handle($line))
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::LivelinessChangedStatus logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::Duration_t")
    {
        if ($line =~ "134.031145")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::Duration_t logging detected\n";
        }
    }
    elsif ($line =~ "Logging DDS::QosPolicyId_t")
    {
        if ($line =~ "DDS::INVALID_QOS_POLICY_ID")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::QosPolicyId_t logging detected\n";
        }
    }
    elsif ($line =~ "Logging mask all")
    {
        if ($line =~ "DDS::STATUS_MASK_ALL")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::STATUS_MASK_ALL logging detected\n";
        }
    }
    elsif ($line =~ "Logging mask none")
    {
        if ($line =~ "DDS::STATUS_MASK_NONE")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::STATUS_MASK_NONE logging detected\n";
        }
    }
    elsif ($line =~ "Logging mask pub:")
    {
        if ($line =~ "PUBLICATION_MATCHED_STATUS")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::PUBLICATION_MATCHED_STATUS logging detected\n";
        }
    }
    elsif ($line =~ "Logging mask pub data:")
    {
        if ($line =~ "DDS::DATA_ON_READERS_STATUS | DDS::PUBLICATION_MATCHED_STATUS")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in DDS::DATA_ON_READERS_STATUS|DDS::PUBLICATION_MATCHED_STATUS logging detected\n";
        }
    }
    elsif ($line =~ "Logging SampleInfo:")
    {
        if ($line =~ "DDS::READ_SAMPLE_STATE" &&
            $line =~ "DDS::NEW_VIEW_STATE" &&
            $line =~ "DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE")
        {
            $found=$found+1;
        }
        else
        {
            print "ERROR: Error in SampleInfo logging detected\n";
        }
    }
}
print "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";

print "\nExpected to find <$expected> - found <$found>\n";
if ($found == $expected) {
    print "OK: Found all expected keywords in the log output.\n"
} else {
    print "ERROR: Expected to find <$expected> keywords but found <$found> keywords.\n";
    $status = 1;
}

exit $status;
