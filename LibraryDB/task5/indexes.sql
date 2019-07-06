create nonclustered index CompositeUsers
on Users(first_name, last_name)

create unique nonclustered index UniqueUsers
on Users(document_number)

create nonclustered index IncludedUsers
on Users(first_name) include (mid_name, last_name)